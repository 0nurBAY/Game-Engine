//Sceneloader.cpp

#include "Core/SceneLoader.h"
#include "Core/AssetLoader.h"
#include <glm/glm.hpp>

void SceneLoader::LoadScene(ParsedResource &resource, ResourceManagerPlus &resourcemanager, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager &scriptmanager,Input *input,Camera &camera){
    std::cout << "SceneLoader::LoadScene: Camera pointer: " << &camera << "\n";
    if(resource.type == "SCENE"){
        currentscene = std::make_unique<Scene>(resource.name);
    }
    else if(resource.type == "ENTITY"){
        currentID = currentscene->AddEntity(resource.name);
        ids.emplace(resource.name,currentID);
    }
    else if(resource.type == "COMPONENT"){
        if(!currentID) return ;
        auto* entity = currentscene->FindEntity(currentID);
        if     (resource.name == "Transform") TransformComponent(entity,resource);
        else if(resource.name == "Material")  MaterialComp(entity,resource,assets);
        else if(resource.name == "Renderer")  RendererComp(entity,resource);
        else if(resource.name == "Sprite")    SpriteComp(entity,resource,assets);
        else if(resource.name == "Animation") AnimationComp(entity);
        else if(resource.name == "Ambient")   AmbientComp(entity,resource);
        else if(resource.name == "Light")     LightComp(entity,resource);
        else if(resource.name == "Script")    ScriptComp(entity,resource,scriptmanager,input);
        else if(resource.name == "Camera")    CameraComp(entity,resource,camera);
        
    }
    else if(resource.type == "ENTITYINIT"){
        if(!currentID) return;
        currentscene->FindEntity(currentID)->init();
    }
    else if(resource.type == "ADDANIMATION"){
        auto* animationcomp = currentscene->FindEntity(currentID)->GetComponent<AnimationComponent>();
        auto it = assets.find(resource.args[0]);
        if(it==assets.end()) return;
        auto& handle = *static_cast<AssetHandle<Animation>*>(it->second.get());
        animationcomp->AddAnimation(resource.name,handle);
    }

}

std::unique_ptr<Scene> SceneLoader::GetScene(){
    return std::move(currentscene);
}

void SceneLoader::TransformComponent (Entity *entity, ParsedResource &resource){
    entity->AddComponent<TransformComp>(glm::vec2(std::stof(resource.args[0]),std::stof(resource.args[1])),std::stof(resource.args[2]),glm::vec2(std::stof(resource.args[3]),std::stof(resource.args[4])));
}
void SceneLoader::MaterialComp(Entity *entity, ParsedResource &resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets){
    
    auto handler = assets.find(resource.args[0]);
    if(handler==assets.end()) return;
    auto& handle = *static_cast<AssetHandle<Material>*>(handler->second.get());
    entity->AddComponent<MaterialComponent>(handle);

}
void SceneLoader::RendererComp  (Entity *entity, ParsedResource &resource){
    entity->AddComponent<RendererComponent>(std::stoi(resource.args[0]),std::stof(resource.args[1]));

}
void SceneLoader::SpriteComp    (Entity *entity, ParsedResource &resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets){
    
    auto handler = assets.find(resource.args[0]);
    if(handler==assets.end()) return;
    auto& handle = *static_cast<AssetHandle<TextureAtlas>*>(handler->second.get());
    entity->AddComponent<SpriteComponent>(handle,resource.args[1]);
}
void SceneLoader::AnimationComp (Entity *entity){
    entity->AddComponent<AnimationComponent>()->AddOwner(entity);
}
void SceneLoader::AmbientComp(Entity *entity, ParsedResource &resource){
    entity->AddComponent<AmbientLightComponent>(glm::vec4(std::stof(resource.args[0]),std::stof(resource.args[1]),std::stof(resource.args[2]),std::stof(resource.args[3])));
}
void SceneLoader::LightComp(Entity *entity, ParsedResource &resource){
    entity->AddComponent<LightComponent>(glm::vec4(std::stof(resource.args[0]),std::stof(resource.args[1]),std::stof(resource.args[2]),std::stof(resource.args[3])),std::stof(resource.args[4]));
}
void SceneLoader::ScriptComp(Entity *entity, ParsedResource &resource,ScriptManager &scriptmanager,Input *input){
    auto* component = entity->AddComponent<ScriptComponent>(scriptmanager.CreateScript(resource.args[0]));
    component->SetEntity(entity);
    component->SetInput(input);
}
void SceneLoader::CameraComp(Entity *entity,ParsedResource& resource,Camera &camera){
    auto it = ids.find(resource.args[0]);
    if(it==ids.end())return;
    uint64_t targetid = it->second;
    std::cout << "SceneLoader::CameraComp: Camera pointer: " << &camera << "\n";
    auto* component = entity->AddComponent<CameraComponent>(&camera,currentscene.get()->FindEntity(targetid));
    
}