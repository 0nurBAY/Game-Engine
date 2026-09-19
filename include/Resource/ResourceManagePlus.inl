//ResourceManagerplus.inl

#pragma once

template<class C, class... Args> std::shared_ptr<C> ResourceManagerPlus::IncludeItem(const std::string &name, Args &&...args){
    auto& map = GetMap<C>();

    auto it = map.find(name);
    if(it != map.end()) return (it->second);

    std::shared_ptr<C> mesh = std::make_shared<C>(std::forward<Args>(args)...);
    map.insert({name,mesh});
    return mesh;
}

template<class C> std::shared_ptr<C> ResourceManagerPlus::GetItem(const std::string &name){
    auto& map = GetMap<C>();
    auto it = map.find(name);
    if(it != map.end()) return (it->second);
    return nullptr;
}

template<class C> bool ResourceManagerPlus::RemoveItem(const std::string &name){
    auto& map = GetMap<C>();
    auto it =map.find(name);
    if(it==map.end())return false;
    std::cout<<"Kullanım sayısı: "<<it->second.use_count()<<"\n";
    if(it->second.use_count()!=1)return false;
    map.erase(it);
    return true;
}

template<class C> std::shared_ptr<C> ResourceManagerPlus::Resolve(const AssetHandle<C> &handle){
    return GetItem<C>(handle.GetName());
}

template<class C> std::unordered_map<std::string, std::shared_ptr<C>> &ResourceManagerPlus::GetMap(){
    if      constexpr (std::is_same_v<C,Texture>)       return textures;
    else if constexpr (std::is_same_v<C,Mesh>)          return meshes;
    else if constexpr (std::is_same_v<C,Shader>)        return shaders;
    else if constexpr (std::is_same_v<C,Material>)      return materials;
    else if constexpr (std::is_same_v<C,TextureAtlas>)  return atlases;
    else if constexpr (std::is_same_v<C,Animation>)     return animations;
    else return;
}
