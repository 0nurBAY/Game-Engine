//AssetLoader.cpp

#include "Resource/AssetLoader.h"

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

void AssetLoader::AssetLoad(ParsedResource &resource, ResourceManagerPlus &resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets){
    if(resource.type == "TEXTURE"){
        TextureLoad(resource, resourcemanager);
        assets.emplace(resource.name,std::make_unique<AssetHandle<Texture>>(resource.name.c_str()));
    }else if(resource.type == "SHADER"){
        ShaderLoad(resource, resourcemanager);
        assets.emplace(resource.name,std::make_unique<AssetHandle<Shader>>(resource.name.c_str()));
    }
    // else if(resource.type == "MESH"){
    //     MeshLoad(resource, resourcemanager);
    // }
    else if(resource.type == "MATERIAL"){
        MaterialLoad(resource, resourcemanager);
        assets.emplace(resource.name,std::make_unique<AssetHandle<Material>>(resource.name.c_str()));
    }else if(resource.type == "TEXTUREATLAS"){
        TextureAtlasLoad(resource, resourcemanager,assets);
        assets.emplace(resource.name,std::make_unique<AssetHandle<TextureAtlas>>(resource.name.c_str()));
    }else if(resource.type == "ANIMATION"){
        AnimationLoad(resource, resourcemanager,assets);
        assets.emplace(resource.name,std::make_unique<AssetHandle<Animation>>(resource.name.c_str()));
    }
    
    
    else if(resource.type == "MATERIAL_ADD"){
        MaterialAdd(resource, resourcemanager,assets);
    }
    else if(resource.type == "ATLAS_ADD"){
        TextureAtlasAdd(resource, resourcemanager);
    }
}

void AssetLoader::TextureLoad(ParsedResource& resource, ResourceManagerPlus& resourcemanager){
    resourcemanager.IncludeItem<Texture>(resource.name,resource.args[0].c_str());
}

void AssetLoader::ShaderLoad(ParsedResource& resource, ResourceManagerPlus& resourcemanager){
    std::string vert = ReadShader(resource.args[0]);
    std::string frag = ReadShader(resource.args[1]);
    resourcemanager.IncludeItem<Shader>(resource.name.c_str(),vert.c_str(),frag.c_str());
}
void AssetLoader::MeshLoad(ParsedResource& resource, ResourceManagerPlus& resourcemanager){}

void AssetLoader::MaterialLoad(ParsedResource& resource, ResourceManagerPlus& resourcemanager){
    resourcemanager.IncludeItem<Material>(resource.name);
}
void AssetLoader::TextureAtlasLoad(ParsedResource& resource, ResourceManagerPlus& resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets){
    auto& handler = assets.find(resource.args[0]);
    if(handler==assets.end()) return;
    auto& handle = *static_cast<AssetHandle<Texture>*>(handler->second.get());
    resourcemanager.IncludeItem<TextureAtlas>(resource.name,handle,std::stof(resource.args[1]),std::stof(resource.args[2]));
}
void AssetLoader::AnimationLoad(ParsedResource& resource, ResourceManagerPlus& resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets){
    std::vector<std::string> anim;
    for(int arg = 2; arg<resource.args.size(); arg++){
        anim.push_back(resource.args[arg]);
    }
    bool loop = resource.args[1] == "loop" ? true : false;
    resourcemanager.IncludeItem<Animation>(resource.name,anim,std::stof(resource.args[0]),loop);
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

void AssetLoader::TextureAtlasAdd(ParsedResource &resource, ResourceManagerPlus &resourcemanager){
    auto char_atlas = resourcemanager.GetItem<TextureAtlas>(resource.name);
    std::string region_name = resource.args[0];
    float x = std::stof(resource.args[1]);
    float y = std::stof(resource.args[2]);
    float w = std::stof(resource.args[3]);
    float h = std::stof(resource.args[4]);
    char_atlas->AddRegion(region_name,x,y,w,h);
}