//ResourceManagerplus.h

#pragma once

#include "Renderer/Texture.h"
#include "Renderer/Shader.h"
#include "Renderer/Mesh.h"
#include "Renderer/Material.h"
#include "Core/Animation.h"
#include "Resource/AssetHandle.h"
#include "Resource/TextureAtlas.h"
#include <memory>
#include <unordered_map>
#include <string>
#include <typeindex>
#include <utility>
class ResourceManagerPlus
{
private:
    std::unordered_map<std::string,std::shared_ptr<Texture>>        textures;
    std::unordered_map<std::string,std::shared_ptr<Shader>>         shaders;
    std::unordered_map<std::string,std::shared_ptr<Mesh>>           meshes;
    std::unordered_map<std::string,std::shared_ptr<Material>>       materials;
    std::unordered_map<std::string,std::shared_ptr<TextureAtlas>>   atlases;
    std::unordered_map<std::string,std::shared_ptr<Animation>>      animations;
public:
    
    
    template<typename C, typename... Args>  std::shared_ptr<C> IncludeItem (const std::string& name, Args&&... args);
    template<typename C>                    std::shared_ptr<C> GetItem     (const std::string& name);
    template<typename C> bool                  RemoveItem  (const std::string& name);
    template<typename C> std::unordered_map<std::string,std::shared_ptr<C>>&    GetMap();
    template<typename C> std::shared_ptr<C> Resolve(const AssetHandle<C>& handle);
};

#include "Resource/ResourceManagePlus.inl"