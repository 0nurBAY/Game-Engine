//ResourceManager.cpp
#include "Resource/ResourceManager.h"

Texture *ResourceManager::IncludeTexture(const std::string& name, const std::string& path){
    auto it = GetTexture(name);
    if(it) return it;
    auto texture = std::make_unique<Texture>(path.c_str());
    Texture* resault = texture.get(); 
    textures.insert({name,std::move(texture)});
    return resault;
}
Texture *ResourceManager::GetTexture(const std::string& name){
    auto it = textures.find(name);
    if(it==textures.end()) return nullptr;
    return it->second.get();
}

void     ResourceManager::RemoveTexture(const std::string& name){
    auto it = textures.find(name);
    if(it!=textures.end()) textures.erase(it);
}