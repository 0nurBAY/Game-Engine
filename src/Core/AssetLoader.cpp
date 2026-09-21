//AssetLoader.cpp

#include "Core/AssetLoader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
std::string ReadShader(const std::string &path){
    std::ifstream file(path);
    if(!file.is_open()){ std::cout<<"!FILE "<<path<<" couldn't open\n"; return "";}
    std::stringstream shader;
    shader << file.rdbuf();

    file.close();
    return shader.str();
}
void AssetLoader::Init(){
    std::cout<< "AssetLoader::Init: Initializing asset loaders...\n";
    loaders.emplace("TEXTURE",     [this](ParsedResource& resource, ResourceManagerPlus& resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets){this->TextureLoad     (resource,resourcemanager,assets);});
    loaders.emplace("SHADER",      [this](ParsedResource& resource, ResourceManagerPlus& resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets){this->ShaderLoad      (resource,resourcemanager,assets);});
    loaders.emplace("MESH",        [this](ParsedResource& resource, ResourceManagerPlus& resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets){this->MeshLoad        (resource,resourcemanager,assets);});
    loaders.emplace("MATERIAL",    [this](ParsedResource& resource, ResourceManagerPlus& resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets){this->MaterialLoad    (resource,resourcemanager,assets);});
    loaders.emplace("TEXTUREATLAS",[this](ParsedResource& resource, ResourceManagerPlus& resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets){this->TextureAtlasLoad(resource,resourcemanager,assets);});
    loaders.emplace("ANIMATION",   [this](ParsedResource& resource, ResourceManagerPlus& resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets){this->AnimationLoad   (resource,resourcemanager,assets);});

    loaders.emplace("MATERIAL_ADD",[this](ParsedResource& resource, ResourceManagerPlus& resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets){this->MaterialAdd     (resource,resourcemanager,assets);});
    loaders.emplace("ATLAS_ADD",   [this](ParsedResource& resource, ResourceManagerPlus& resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets){this->TextureAtlasAdd (resource,resourcemanager,assets);});
    
    std::cout<< "AssetLoader::Init: Asset loaders initialized successfully.\n";

}
void AssetLoader::LoadAsset(ParsedResource &resource, ResourceManagerPlus &resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets){
    
    currentline++;
    resource.line = this->currentline;


    printf("FILE: %s\tLINE: %llu\n\t-TYPE: %s\n\t-NAME: %s\n",resource.file.c_str(), static_cast<unsigned long long>(resource.line),resource.type.c_str(),resource.name.c_str());
    for(auto& arg:resource.args){
        printf("\t-ARG: %s\n",arg.c_str());
    }
    std::cout<<"\n";
    std::cout<< "Asset Type Lenght: " << resource.type.length() << "\n";
    auto it = loaders.find(resource.type.c_str());
    if(it == loaders.end()) {
        std::cout << "AssetLoader::LoadAsset: Unknown resource type: " << "-" << resource.type << "-" << " at line " << resource.line << " in file " << resource.file << "\n";
        return;
    }
    it->second(resource,resourcemanager,assets);
    
}

void AssetLoader::TextureLoad(ParsedResource& resource, ResourceManagerPlus& resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets){
    resourcemanager.IncludeItem<Texture>(resource.name,resource.args[0].c_str());
    assets.emplace(resource.name,std::make_unique<AssetHandle<Texture>>(resource.name.c_str()));
}
void AssetLoader::ShaderLoad(ParsedResource& resource, ResourceManagerPlus& resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets){
    std::string vert = ReadShader(resource.args[0]);
    std::string frag = ReadShader(resource.args[1]);
    resourcemanager.IncludeItem<Shader>(resource.name.c_str(),vert.c_str(),frag.c_str());
    assets.emplace(resource.name,std::make_unique<AssetHandle<Shader>>(resource.name.c_str()));

}
void AssetLoader::MeshLoad(ParsedResource& resource, ResourceManagerPlus& resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets){}
void AssetLoader::MaterialLoad(ParsedResource& resource, ResourceManagerPlus& resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets){
    resourcemanager.IncludeItem<Material>(resource.name);
    assets.emplace(resource.name,std::make_unique<AssetHandle<Material>>(resource.name.c_str()));
}
void AssetLoader::TextureAtlasLoad(ParsedResource& resource, ResourceManagerPlus& resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets){
    auto& handler = assets.find(resource.args[0]);
    if(handler==assets.end()) return;
    auto& handle = *static_cast<AssetHandle<Texture>*>(handler->second.get());
    resourcemanager.IncludeItem<TextureAtlas>(resource.name,handle,std::stof(resource.args[1]),std::stof(resource.args[2]));
    assets.emplace(resource.name,std::make_unique<AssetHandle<TextureAtlas>>(resource.name.c_str()));
}
void AssetLoader::AnimationLoad(ParsedResource& resource, ResourceManagerPlus& resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets){
    std::vector<std::string> anim;
    for(int arg = 2; arg<resource.args.size(); arg++){
        anim.push_back(resource.args[arg]);
    }
    bool loop = resource.args[1] == "loop" ? true : false;
    resourcemanager.IncludeItem<Animation>(resource.name,anim,std::stof(resource.args[0]),loop);
    assets.emplace(resource.name,std::make_unique<AssetHandle<Animation>>(resource.name.c_str()));
}


void AssetLoader::MaterialAdd(ParsedResource& resource, ResourceManagerPlus& resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets){
    if(resource.name == "TEXTURE"){
        auto handler = assets.find(resource.args[1]);
        if(handler == assets.end()) return;
        auto& textureHandle = *static_cast<AssetHandle<Texture>*>(handler->second.get());
        resourcemanager.GetItem<Material>(resource.args[0])->SetTexture(textureHandle);
    }
    else if(resource.name == "NORMAL"){
        auto handler = assets.find(resource.args[1]);
        if(handler == assets.end()) return;
        auto& textureHandle = *static_cast<AssetHandle<Texture>*>(handler->second.get());
        resourcemanager.GetItem<Material>(resource.args[0])->SetNormal(textureHandle);
    }
    else if(resource.name == "SHADER"){
        auto handler = assets.find(resource.args[1]);
        if(handler == assets.end()) return;
        auto& textureHandle = *static_cast<AssetHandle<Shader>*>(handler->second.get());
        resourcemanager.GetItem<Material>(resource.args[0])->SetShader(textureHandle);
    }
}
void AssetLoader::TextureAtlasAdd(ParsedResource &resource, ResourceManagerPlus &resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets){
    auto char_atlas = resourcemanager.GetItem<TextureAtlas>(resource.name);
    std::string region_name = resource.args[0];
    float x = std::stof(resource.args[1]);
    float y = std::stof(resource.args[2]);
    float w = std::stof(resource.args[3]);
    float h = std::stof(resource.args[4]);
    char_atlas->AddRegion(region_name,x,y,w,h);
}