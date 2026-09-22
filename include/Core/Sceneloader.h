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
    uint64_t currentline = 0;
    std::unordered_map<std::string,std::function<void(Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera)>> commands;
    std::unique_ptr<Scene> currentscene = nullptr;
    std::unordered_map<std::string,uint64_t> ids;
    uint64_t currentID;
    void TransformComponent (Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera);
    void MaterialComp       (Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera);
    void RendererComp       (Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera);
    void SpriteComp         (Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera);
    void AnimationComp      (Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera);
    void LightComp          (Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera);
    void AmbientComp        (Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera);
    void ScriptComp         (Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera);
    void CameraComp         (Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera);
    void CreateScene        (Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera);
    void CreateEntity       (Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera);
    void EntityInit         (Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera);
    void AddComponent       (Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera);
    void AddAnimation       (Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera);
public:
    void Init();
    void LineCounter(){currentline++;}
    void LoadScene(ParsedResource& resource, ResourceManagerPlus& resourcemanager,std::unordered_map<std::string,std::unique_ptr<AssetHandleBase>>& assets,ScriptManager& scriptmanager,Input* input, Camera& camera);
    std::unique_ptr<Scene> GetScene();
};