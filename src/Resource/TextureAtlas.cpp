//TextureAtlas.cpp

#include "Resource/TextureAtlas.h"

TextureAtlas::TextureAtlas(AssetHandle<Texture> texture,float textureWidth ,float textureHeight):
    texture(texture),
    textureWidth(textureWidth),
    textureHeight(textureHeight){}

void TextureAtlas::AddRegion(const std::string &name, float x,float y,float w,float h){
    Atlas item({x,y,w,h});
    sprites.insert({name,item});
}
Atlas *TextureAtlas::GetSprite(const std::string &name){
    auto it = sprites.find(name);
    if(it==sprites.end())return nullptr;
    return &it->second;
}
AtlasUV TextureAtlas::GetUV(const std::string &name){
    auto it = sprites.find(name);
    if(it==sprites.end())return {};
    const Atlas& sprite = it->second;

    AtlasUV res;
    res.min.x = sprite.x/textureWidth;
    res.max.x = (sprite.x+sprite.w)/textureWidth;
    res.min.y = (sprite.y/textureHeight);
    res.max.y = (sprite.y+sprite.h)/textureHeight;
    return res;

}
AssetHandle<Texture> TextureAtlas::GetTexture() const{
    return texture;
}