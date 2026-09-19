//TextureAtlas.h
#pragma once

#include "Resource/AssetHandle.h"
#include "Renderer/Texture.h"

#include <unordered_map>
#include <glm/glm.hpp>

struct Atlas
{
    float x;
    float y;
    float w;
    float h;
};

struct AtlasUV
{
    glm::vec2 min;
    glm::vec2 max;
};

class TextureAtlas
{
private:
    std::unordered_map<std::string,Atlas> sprites;
    AssetHandle<Texture> texture;
    float textureWidth ;
    float textureHeight;
public:
    TextureAtlas(AssetHandle<Texture> texture,float textureWidth ,float textureHeight);
    void AddRegion(const std::string& name, float x,float y,float w,float h);
    Atlas*   GetSprite(const std::string& name);
    AtlasUV GetUV(const std::string& name);
    AssetHandle<Texture> GetTexture() const;
};

