//AssetLoader.h
#pragma once
#include "Resource/ResourceManagerplus.h"
#include "Resource/AssetHandleBase.h"

#include <string>
#include <vector>
#include <unordered_map>
struct ParsedResource{
    std::string file;
    uint64_t line;
    std::string type;
    std::string name;
    std::vector<std::string> args;
};

#pragma once
class AssetLoader
{
private:
    uint64_t currentline = 0;
    std::unordered_map<std::string,std::function<void(ParsedResource& resource, ResourceManagerPlus& resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets)>> loaders;

    void TextureLoad     (ParsedResource& resource, ResourceManagerPlus& resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets);
    void ShaderLoad      (ParsedResource& resource, ResourceManagerPlus& resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets);
    void MeshLoad        (ParsedResource& resource, ResourceManagerPlus& resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets);
    void MaterialLoad    (ParsedResource& resource, ResourceManagerPlus& resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets);
    void TextureAtlasLoad(ParsedResource& resource, ResourceManagerPlus& resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets);
    void AnimationLoad   (ParsedResource& resource, ResourceManagerPlus& resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets);

    void MaterialAdd     (ParsedResource& resource, ResourceManagerPlus& resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets);
    void TextureAtlasAdd (ParsedResource& resource, ResourceManagerPlus& resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets);
public:
    void Init();
    void LineCounter(){currentline++;}
    void LoadAsset(ParsedResource& resource, ResourceManagerPlus& resourcemanager,std::unordered_map<std::string,std::unique_ptr<AssetHandleBase>>& assets);
};