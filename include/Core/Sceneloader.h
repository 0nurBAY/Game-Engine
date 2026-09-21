//Sceneloader.h
#pragma once

#include "Resource/ResourceManagerplus.h"
#include "Resource/AssetHandleBase.h"
#include "Scene/Scene.h"
#include "Core/ScriptManager.h"
#include "Core/Input.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>


struct ParsedResource;

class SceneLoader
{
private:
    std::unique_ptr<Scene> currentscene = nullptr;
    std::unordered_map<std::string,uint64_t> ids;
    uint64_t currentID;
    void TransformComponent (Entity* entity,ParsedResource& resource);
    void MaterialComp       (Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets);
    void RendererComp       (Entity* entity,ParsedResource& resource);
    void SpriteComp         (Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets);
    void AnimationComp      (Entity* entity);
    void AmbientComp        (Entity* entity,ParsedResource& resource);
    void LightComp          (Entity* entity,ParsedResource& resource);
    void ScriptComp         (Entity* entity,ParsedResource& resource,ScriptManager& scriptmanager,Input* input);
    void CameraComp         (Entity* entity,ParsedResource& resource,Camera& camera);
public:
    void LoadScene(ParsedResource& resource, ResourceManagerPlus& resourcemanager,std::unordered_map<std::string,std::unique_ptr<AssetHandleBase>>& assets,ScriptManager& scriptmanager,Input* input, Camera& camera);
    std::unique_ptr<Scene> GetScene();
};