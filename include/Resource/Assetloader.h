//AssetLoader.h
#include "Resource/ResourceManagerplus.h"
#include "Resource/AssetHandleBase.h"

#include <string>
#include <vector>
#include <unordered_map>
struct ParsedResource{
    std::string type;
    std::string name;
    std::vector<std::string> args;
};

#pragma once
class AssetLoader
{
private:
    void TextureLoad     (ParsedResource& resource, ResourceManagerPlus& resourcemanager);
    void ShaderLoad      (ParsedResource& resource, ResourceManagerPlus& resourcemanager);
    void MeshLoad        (ParsedResource& resource, ResourceManagerPlus& resourcemanager);
    void MaterialLoad    (ParsedResource& resource, ResourceManagerPlus& resourcemanager);
    void TextureAtlasLoad(ParsedResource& resource, ResourceManagerPlus& resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets);
    void AnimationLoad   (ParsedResource& resource, ResourceManagerPlus& resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets);

    void MaterialAdd     (ParsedResource& resource, ResourceManagerPlus& resourcemanager,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets);
    void TextureAtlasAdd (ParsedResource& resource, ResourceManagerPlus& resourcemanager);
public:
    void AssetLoad(ParsedResource& resource, ResourceManagerPlus& resourcemanager,std::unordered_map<std::string,std::unique_ptr<AssetHandleBase>>& assets);
};