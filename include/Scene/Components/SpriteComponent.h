//SpriteComponent.h

#pragma once
#include "Scene/Components/Component.h"
#include "Resource/AssetHandle.h"
#include "Resource/TextureAtlas.h"
#include <string>
#include <glm/glm.hpp>

class SpriteComponent: public Component
{
    
private:
    AssetHandle<TextureAtlas> atlas;
    std::string sprite;
public:
    SpriteComponent(AssetHandle<TextureAtlas>& atlas,const std::string& name);
    AssetHandle<TextureAtlas> GetAtlas() const;
    const std::string& GetSprite() const;
    void SetSprite(const std::string& new_sprite);
};
