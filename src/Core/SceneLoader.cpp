//Sceneloader.cpp

#include "Core/SceneLoader.h"
#include "Core/AssetLoader.h"
#include <glm/glm.hpp>
void SceneLoader::Init(){
        
    commands.emplace("SCENE",[this](Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera){currentscene = std::make_unique<Scene>(resource.name);});
    commands.emplace("ENTITY",[this](Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera)
    {   currentID = currentscene->AddEntity(resource.name);
        ids.emplace(resource.name,currentID);
    });
    commands.emplace("COMPONENT",[this](Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera)
    {   if(!currentID) return ;
        auto* entitya = currentscene->FindEntity(currentID);
        auto it = commands.find(resource.name);
        if(it == commands.end()) return;
        it->second(entitya,resource,assets,scriptmanager,input,camera);
    });
    commands.emplace("ENTITYINIT",[this](Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera)
    {   if(!currentID) return;
        currentscene->FindEntity(currentID)->init();
    });
    commands.emplace("ADDANIMATION",[this](Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera)
    {   if(!currentID) return;
        auto* animationcomp = currentscene->FindEntity(currentID)->GetComponent<AnimationComponent>();
        auto it = assets.find(resource.args[0]);
        if(it==assets.end()) return;
        auto& handle = *static_cast<AssetHandle<Animation>*>(it->second.get());
        animationcomp->AddAnimation(resource.name,handle);});

    commands.emplace("Transform",   [this](Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera){this->TransformComponent(entity,resource,assets,scriptmanager,input,camera);});
    commands.emplace("Material",    [this](Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera){this->MaterialComp(entity,resource,assets,scriptmanager,input,camera);});
    commands.emplace("Renderer",    [this](Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera){this->RendererComp(entity,resource,assets,scriptmanager,input,camera);});
    commands.emplace("Sprite",      [this](Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera){this->SpriteComp(entity,resource,assets,scriptmanager,input,camera);});
    commands.emplace("Animation",   [this](Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera){this->AnimationComp(entity,resource,assets,scriptmanager,input,camera);});
    commands.emplace("Ambient",     [this](Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera){this->AmbientComp(entity,resource,assets,scriptmanager,input,camera);});
    commands.emplace("Light",       [this](Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera){this->LightComp(entity,resource,assets,scriptmanager,input,camera);});
    commands.emplace("Script",      [this](Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera){this->ScriptComp(entity,resource,assets,scriptmanager,input,camera);});
    commands.emplace("Camera",      [this](Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera){this->CameraComp(entity,resource,assets,scriptmanager,input,camera);});

}
void SceneLoader::LoadScene(ParsedResource &resource, ResourceManagerPlus &resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager &scriptmanager,Input *input,Camera &camera){
    // std::cout << "SceneLoader::LoadScene: Camera pointer: " << &camera << "\n";
    this->currentline++;
    resource.line = this->currentline;

    printf("FILE: %s\tLINE: %llu\n\t-TYPE: %s\n\t-NAME: %s\n",resource.file.c_str(), static_cast<unsigned long long>(resource.line),resource.type.c_str(),resource.name.c_str());
    for(auto& arg:resource.args){
        printf("\t-ARG: %s\n",arg.c_str());
    }
    std::cout<<"\n";
    
    auto it = commands.find(resource.type.c_str());
    if(it == commands.end()) {
        std::cout << "SceneLoader::LoadScene: Unknown resource type: " << "-" << resource.type << "-" << " at line " << resource.line << " in file " << resource.file << "\n";
        return;
    }
    it->second(nullptr,resource,assets,scriptmanager,input,camera);

}

std::unique_ptr<Scene> SceneLoader::GetScene(){
    return std::move(currentscene);
}

void SceneLoader::TransformComponent (Entity *entity, ParsedResource &resource, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets, ScriptManager &scriptmanager, Input *input, Camera &camera){
    entity->AddComponent<TransformComp>(glm::vec2(std::stof(resource.args[0]),std::stof(resource.args[1])),std::stof(resource.args[2]),glm::vec2(std::stof(resource.args[3]),std::stof(resource.args[4])));
}
void SceneLoader::MaterialComp(Entity *entity, ParsedResource &resource, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets, ScriptManager &scriptmanager, Input *input, Camera &camera){
    
    auto handler = assets.find(resource.args[0]);
    if(handler==assets.end()) return;
    auto& handle = *static_cast<AssetHandle<Material>*>(handler->second.get());
    entity->AddComponent<MaterialComponent>(handle);

}
void SceneLoader::RendererComp  (Entity *entity, ParsedResource &resource, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets, ScriptManager &scriptmanager, Input *input, Camera &camera){
    entity->AddComponent<RendererComponent>(std::stoi(resource.args[0]),std::stof(resource.args[1]));

}
void SceneLoader::SpriteComp    (Entity *entity, ParsedResource &resource, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets, ScriptManager &scriptmanager, Input *input, Camera &camera){
    
    auto handler = assets.find(resource.args[0]);
    if(handler==assets.end()) return;
    auto& handle = *static_cast<AssetHandle<TextureAtlas>*>(handler->second.get());
    entity->AddComponent<SpriteComponent>(handle,resource.args[1]);
}
void SceneLoader::AnimationComp (Entity *entity, ParsedResource &resource, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets, ScriptManager &scriptmanager, Input *input, Camera &camera){
    entity->AddComponent<AnimationComponent>()->AddOwner(entity);
}
void SceneLoader::AmbientComp(Entity *entity, ParsedResource &resource, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets, ScriptManager &scriptmanager, Input *input, Camera &camera){
    entity->AddComponent<AmbientLightComponent>(glm::vec4(std::stof(resource.args[0]),std::stof(resource.args[1]),std::stof(resource.args[2]),std::stof(resource.args[3])));
}
void SceneLoader::LightComp(Entity *entity, ParsedResource &resource, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets, ScriptManager &scriptmanager, Input *input, Camera &camera){
    entity->AddComponent<LightComponent>(glm::vec4(std::stof(resource.args[0]),std::stof(resource.args[1]),std::stof(resource.args[2]),std::stof(resource.args[3])),std::stof(resource.args[4]));
}
void SceneLoader::ScriptComp(Entity *entity, ParsedResource &resource, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets, ScriptManager &scriptmanager, Input *input, Camera &camera){
    auto* component = entity->AddComponent<ScriptComponent>(scriptmanager.CreateScript(resource.args[0]));
    component->SetEntity(entity);
    component->SetInput(input);
}
void SceneLoader::CameraComp(Entity *entity, ParsedResource &resource, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets, ScriptManager &scriptmanager, Input *input, Camera &camera){
    auto it = ids.find(resource.args[0]);
    if(it==ids.end())return;
    uint64_t targetid = it->second;
    std::cout << "SceneLoader::CameraComp: Camera pointer: " << &camera << "\n";
    auto* component = entity->AddComponent<CameraComponent>(&camera,currentscene.get()->FindEntity(targetid));
    
}