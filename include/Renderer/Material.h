//Material.h
#pragma once


#include "Resource/AssetHandle.h"
#include "Renderer/Texture.h"
#include "Renderer/Shader.h"
#include <glm/glm.hpp>
#include <memory>
class ResourceManagerPlus;

class Material
{
private:
    
    AssetHandle<Texture> texture;
    AssetHandle<Texture> normal;
    AssetHandle<Shader>  shader ;
    glm::vec4 color = glm::vec4(1.0f,1.0f,1.0f,1.0f);
    bool gradient;
public:
    Material();
    void SetTexture(AssetHandle<Texture> new_texure);
    void SetNormal (AssetHandle<Texture> new_normal);
    void SetColor(const glm::vec4& new_color);
    void SetShader(AssetHandle<Shader> new_shader);
    void SetGradient(bool new_gradient);
    
    AssetHandle<Texture>    GetTexture() const;
    AssetHandle<Texture>    GetNormal() const;
    AssetHandle<Shader>     GetShader()  const;
    glm::vec4   GetColor  () const;
    bool        GetGradient()const;

    void        Apply(ResourceManagerPlus& resourcemanager);
    void        ApplyNormal(ResourceManagerPlus& resourcemanager);
    
};