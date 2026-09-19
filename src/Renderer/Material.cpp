//Material.cpp

#include "Renderer/Material.h"
#include "Resource/ResourceManagerplus.h"

Material::Material(){}

void Material::SetTexture(AssetHandle<Texture> new_texure){
    texture = new_texure;
}
void Material::SetNormal(AssetHandle<Texture> new_normal){
    normal = new_normal;
}
void Material::SetColor(const glm::vec4 &new_color){
    color = new_color;   
}
void Material::SetShader(AssetHandle<Shader> new_shader){
    shader = new_shader;
}
void Material::SetGradient(bool new_gradient){
    gradient = new_gradient;
}


AssetHandle<Texture> Material::GetTexture()const{
    return texture;
}

AssetHandle<Texture> Material::GetNormal()const{
    return normal;
}

glm::vec4 Material::GetColor ()const{
    return color;
}
bool Material::GetGradient   ()const{
    return gradient;
}
AssetHandle<Shader> Material::GetShader() const{
    return shader;
}
void Material::Apply(ResourceManagerPlus &resourcemanager){
    if(!shader.IsValid())return;
    auto shader_asset = resourcemanager.Resolve<Shader>(shader.GetName());
    if(texture.IsValid()){
        auto texture_asset = resourcemanager.Resolve<Texture>(texture.GetName());
        texture_asset->Bind(0);
        shader_asset ->SetInt("ourTexture",0);
    }
    if(gradient){
        shader_asset->SetVec4("gradientCenter",color);
        shader_asset->SetVec4("gradientEdge",glm::vec4(0.1f,0.0015f,0.15f,1.0f));
        return;
    }
    shader_asset->SetVec4("solidColor",color);
}
void Material::ApplyNormal(ResourceManagerPlus &resourcemanager){
    if(!shader.IsValid())return;
    auto shader_asset = resourcemanager.Resolve<Shader>(shader.GetName());
    if(normal.IsValid()){    
        auto normal_asset = resourcemanager.Resolve<Texture>(normal.GetName());
        normal_asset->Bind(1);
        shader_asset ->SetInt("NormalMap",1);
        return;
    }
}