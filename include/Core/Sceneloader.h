//Sceneloader.h
#pragma once

#include "Resource/ResourceManagerplus.h"
#include "Resource/AssetHandleBase.h"
#include "Scene/Scene.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>


struct ParsedResource;

class SceneLoader
{
private:
    std::unique_ptr<Scene> currentscene = nullptr;
    uint64_t currentID;
    void TransformComponent (Entity* entity,ParsedResource& resource);
    void MaterialComp       (Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets);
    void RendererComp       (Entity* entity,ParsedResource& resource);
    void SpriteComp         (Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets);
    void AnimationComp      (Entity* entity);
    void AmbientComp   (Entity* entity,ParsedResource& resource);
    void LightComp          (Entity* entity,ParsedResource& resource);
public:
    void LoadScene(ParsedResource& resource, ResourceManagerPlus& resourcemanager,std::unordered_map<std::string,std::unique_ptr<AssetHandleBase>>& assets);
    std::unique_ptr<Scene> GetScene();
};