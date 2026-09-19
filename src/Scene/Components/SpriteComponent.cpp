//SpriteComponent.cpp

#include "Scene/Components/SpriteComponent.h"

SpriteComponent::SpriteComponent(AssetHandle<TextureAtlas> &atlas, const std::string &name):atlas(atlas),sprite(name){}

AssetHandle<TextureAtlas> SpriteComponent::GetAtlas() const{
    return atlas;
}
const std::string &SpriteComponent::GetSprite() const{
    return sprite;
}
void SpriteComponent::SetSprite(const std::string &new_sprite){
    sprite = new_sprite;
}