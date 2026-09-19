//ResourseManager.h
#pragma once

#include "Renderer/Texture.h"
#include <memory>
#include <unordered_map>
#include <string>
class ResourceManager
{
private:
    std::unordered_map<std::string,std::unique_ptr<Texture>> textures;
public:
    
    
    Texture* IncludeTexture (const std::string& name, const std::string& path);
    Texture* GetTexture     (const std::string& name);
    void     RemoveTexture  (const std::string& name);
    
};

