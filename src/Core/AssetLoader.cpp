//AssetLoader.cpp

#include "Core/AssetLoader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


std::string ReadShader(const std::string &path){
    std::ifstream file(path);
    if(!file.is_open()){ throw std::runtime_error("File not found: " + path);}
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
    for(auto arg:resource.args){
        printf("\t-ARG: %s\n",arg.c_str());
    }
    // std::cout<<"\n";
    // std::cout<< "Asset Type Lenght: " << resource.type.length() << "\n";
    auto it = loaders.find(resource.type.c_str());
    if(it == loaders.end()) throw std::runtime_error("No loader found for " + resource.type + "\n" + resource.file + " - " +std::to_string(resource.line));
    if(resource.name.empty()) throw std::runtime_error("No enough arguments for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
    it->second(resource,resourcemanager,assets);
    
}

void AssetLoader::TextureLoad(ParsedResource& resource, ResourceManagerPlus& resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets){
    if(resource.args.size()<1) throw std::runtime_error("No enough arguments for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
    if(resource.args.size()>1) throw std::runtime_error("Too many arguments for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
    try{
        std::ifstream file(resource.args[0]);
        if(!file.is_open()) throw std::runtime_error("File not found: " + resource.args[0]);
    }
    catch(const std::exception& e){
        throw std::runtime_error("Invalid argument for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line) + "\nArgument: " + resource.args[0]);
    }
    resourcemanager.IncludeItem<Texture>(resource.name,resource.args[0].c_str());
    assets.emplace(resource.name,std::make_unique<AssetHandle<Texture>>(resource.name.c_str()));
}
void AssetLoader::ShaderLoad(ParsedResource& resource, ResourceManagerPlus& resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets){
    if(resource.args.size()<2) throw std::runtime_error("No enough arguments for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
    if(resource.args.size()>2) throw std::runtime_error("Too many arguments for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
    std::string vert;
    std::string frag;
    try{ 
        vert = ReadShader(resource.args[0]);
        frag = ReadShader(resource.args[1]);
    }
    catch(const std::exception& e){
        throw std::runtime_error("Invalid argument for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line) + "\nArgument: " + resource.args[0] +"or " + resource.args[1]);
    }
    resourcemanager.IncludeItem<Shader>(resource.name.c_str(),vert.c_str(),frag.c_str());
    assets.emplace(resource.name,std::make_unique<AssetHandle<Shader>>(resource.name.c_str()));
}
void AssetLoader::MeshLoad(ParsedResource& resource, ResourceManagerPlus& resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets){}
void AssetLoader::MaterialLoad(ParsedResource& resource, ResourceManagerPlus& resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets){
    resourcemanager.IncludeItem<Material>(resource.name);
    assets.emplace(resource.name,std::make_unique<AssetHandle<Material>>(resource.name.c_str()));
}
void AssetLoader::TextureAtlasLoad(ParsedResource& resource, ResourceManagerPlus& resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets){
    if(resource.args.size()<3) throw std::runtime_error("No enough arguments for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
    if(resource.args.size()>3) throw std::runtime_error("Too many arguments for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
    auto handler = assets.find(resource.args[0]);
    if(handler==assets.end()) throw std::runtime_error("Invalid argument for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line) + "\nArgument: " + resource.args[0]);
    auto handle = *static_cast<AssetHandle<Texture>*>(handler->second.get());
    try{
        std::stof(resource.args[1]);
        std::stof(resource.args[2]);
    }
    catch(const std::exception& e){
        throw std::runtime_error("Invalid argument for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line) + "\nArgument: " + resource.args[1] +" or " + resource.args[2]);
    }
    resourcemanager.IncludeItem<TextureAtlas>(resource.name,handle,std::stof(resource.args[1]),std::stof(resource.args[2]));
    assets.emplace(resource.name,std::make_unique<AssetHandle<TextureAtlas>>(resource.name.c_str()));
}

void AssetLoader::AnimationLoad(ParsedResource& resource, ResourceManagerPlus& resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets){
    if(resource.args.size()<3) throw std::runtime_error("No enough arguments for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
    bool loop = false;
    try{
        std::stof(resource.args[0]);
        if(resource.args[1] == "loop"){
            loop = true;
        }
        else if(resource.args[1] != "once"){
            throw std::runtime_error("Invalid argument for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line) + "\nArgument: " + resource.args[1]);
        }
    }
    catch(const std::exception& e){
        throw std::runtime_error("Invalid argument for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line) + "\nArgument: " + resource.args[1]);
    }
    std::vector<std::string> anim;
    for(int arg = 2; arg<resource.args.size(); arg++){
        if(loaded_assets.find(resource.args[arg])==loaded_assets.end()) throw std::runtime_error("Invalid argument for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line) + "\nArgument: " + resource.args[arg]);
        anim.push_back(resource.args[arg]);
    }
    resourcemanager.IncludeItem<Animation>(resource.name,anim,std::stof(resource.args[0]),loop);
    assets.emplace(resource.name,std::make_unique<AssetHandle<Animation>>(resource.name.c_str()));
}


void AssetLoader::MaterialAdd(ParsedResource& resource, ResourceManagerPlus& resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets){
    if(resource.args.size()<2) throw std::runtime_error("No enough arguments for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
    if(resource.args.size()>2) throw std::runtime_error("Too many arguments for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
    
    auto material = resourcemanager.GetItem<Material>(resource.args[0]);
    if(!material) throw std::runtime_error("Invalid argument for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line) + "\nArgument: " + resource.args[0]);
    auto handler = assets.find(resource.args[1]);
    if(handler == assets.end()) throw std::runtime_error("Invalid argument for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line) + "\nArgument: " + resource.args[1]);
        
    if(resource.name == "TEXTURE"){
        auto textureHandle = *static_cast<AssetHandle<Texture>*>(handler->second.get());
        material->SetTexture(textureHandle);
    }
    else if(resource.name == "NORMAL"){
        auto textureHandle = *static_cast<AssetHandle<Texture>*>(handler->second.get());
        material->SetNormal(textureHandle);
    }
    else if(resource.name == "SHADER"){
        auto textureHandle = *static_cast<AssetHandle<Shader>*>(handler->second.get());
        material->SetShader(textureHandle);
    }
    else{
        throw std::runtime_error("Invalid argument for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line) + "\nArgument: " + resource.name);
    }
}
void AssetLoader::TextureAtlasAdd(ParsedResource &resource, ResourceManagerPlus &resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets){
    if(resource.args.size()<5) throw std::runtime_error("No enough arguments for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
    if(resource.args.size()>5) throw std::runtime_error("Too many arguments for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
    auto char_atlas = resourcemanager.GetItem<TextureAtlas>(resource.name);
    std::string region_name = resource.args[0];
    float x;
    float y;
    float w;
    float h;
    try{
        x = std::stof(resource.args[1]);
        y = std::stof(resource.args[2]);
        w = std::stof(resource.args[3]);
        h = std::stof(resource.args[4]);
    }
    catch(const std::exception& e){
        throw std::runtime_error("Invalid argument for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line) + "\nArgument:\n" + resource.args[1] + " or " + resource.args[2] + " or " + resource.args[3] + " or " + resource.args[4]);
    }
    char_atlas->AddRegion(region_name,x,y,w,h);
    loaded_assets.insert(region_name);
}