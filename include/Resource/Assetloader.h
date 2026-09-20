//AssetLoader.h
#include "Resource/ResourceManagerplus.h"
#include <string>
#include <vector>

struct ParsedResource{
    std::string type;
    std::string name;
    std::vector<std::string> args;
};

#pragma once
class AssetLoader
{
private:
    void TextureLoad();
    void ShaderLoad();
public:
    void AssetLoad(ParsedResource& resource, ResourceManagerPlus& resourcemanager);
};