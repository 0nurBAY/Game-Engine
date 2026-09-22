//Sceneloader.cpp

#include "Core/SceneLoader.h"
#include "Core/AssetLoader.h"
#include <glm/glm.hpp>
#include <stdexcept>
void SceneLoader::Init(){
        
    commands.emplace("SCENE",[this](Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera){CreateScene(entity,resource,assets,scriptmanager,input,camera);});
    commands.emplace("ENTITY",[this](Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera){CreateEntity(entity,resource,assets,scriptmanager,input,camera);});
    commands.emplace("COMPONENT",[this](Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera){AddComponent(entity,resource,assets,scriptmanager,input,camera);});
    commands.emplace("ENTITYINIT",[this](Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera){EntityInit(entity,resource,assets,scriptmanager,input,camera);});
    commands.emplace("ADDANIMATION",[this](Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera){AddAnimation(entity,resource,assets,scriptmanager,input,camera);});

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
    if(resource.name.empty()) throw std::runtime_error("No enough arguments for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
    auto it = commands.find(resource.type.c_str());
    if(it == commands.end()) throw std::runtime_error("No enough arguments for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
    it->second(nullptr,resource,assets,scriptmanager,input,camera);

}

std::unique_ptr<Scene> SceneLoader::GetScene(){
    return std::move(currentscene);
}

void SceneLoader::TransformComponent (Entity *entity, ParsedResource &resource, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets, ScriptManager &scriptmanager, Input *input, Camera &camera){
    
    if(resource.args.size()<5) throw std::runtime_error("No enough arguments for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
    if(resource.args.size()>5) throw std::runtime_error("Too many arguments for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
    for(auto& arg:resource.args){
        try{
            std::stof(arg);
        }
        catch(const std::exception& e){
            throw std::runtime_error("Invalid argument for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line) + "\nArgument: " + arg);
        }
    }
    entity->AddComponent<TransformComp>(glm::vec2(std::stof(resource.args[0]),std::stof(resource.args[1])),std::stof(resource.args[2]),glm::vec2(std::stof(resource.args[3]),std::stof(resource.args[4])));
}
void SceneLoader::MaterialComp(Entity *entity, ParsedResource &resource, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets, ScriptManager &scriptmanager, Input *input, Camera &camera){
    if(resource.args.size()<1) throw std::runtime_error("No enough arguments for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
    if(resource.args.size()>1) throw std::runtime_error("Too many arguments for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
    
    auto handler = assets.find(resource.args[0]);
    if(handler==assets.end()) throw std::runtime_error("Invalid argument for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line) + "\nArgument: " + resource.args[0]);
    auto& handle = *static_cast<AssetHandle<Material>*>(handler->second.get());
    entity->AddComponent<MaterialComponent>(handle);

}
void SceneLoader::RendererComp  (Entity *entity, ParsedResource &resource, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets, ScriptManager &scriptmanager, Input *input, Camera &camera){
    if(resource.args.size()<2) throw std::runtime_error("No enough arguments for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
    if(resource.args.size()>2) throw std::runtime_error("Too many arguments for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
    
    try{
        std::stoi(resource.args[0]);
        std::stof(resource.args[1]);
    }
    catch(const std::exception& e){
        throw std::runtime_error("Invalid argument for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line) + "\nArgument: " + resource.args[0] + " or " + resource.args[1]);
    }
    entity->AddComponent<RendererComponent>(std::stoi(resource.args[0]),std::stof(resource.args[1]));

}
void SceneLoader::SpriteComp    (Entity *entity, ParsedResource &resource, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets, ScriptManager &scriptmanager, Input *input, Camera &camera){
    if(resource.args.size()<2) throw std::runtime_error("No enough arguments for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
    if(resource.args.size()>2) throw std::runtime_error("Too many arguments for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
    auto handler = assets.find(resource.args[0]);
    if(handler==assets.end()) throw std::runtime_error("Invalid argument for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line) + "\nArgument: " + resource.args[0]);
    auto& handle = *static_cast<AssetHandle<TextureAtlas>*>(handler->second.get());
    entity->AddComponent<SpriteComponent>(handle,resource.args[1]);
}
void SceneLoader::AnimationComp (Entity *entity, ParsedResource &resource, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets, ScriptManager &scriptmanager, Input *input, Camera &camera){
    if(resource.args.size()>0) throw std::runtime_error("Too many arguments for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
    entity->AddComponent<AnimationComponent>()->AddOwner(entity);
}
void SceneLoader::AmbientComp(Entity *entity, ParsedResource &resource, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets, ScriptManager &scriptmanager, Input *input, Camera &camera){
    if(resource.args.size()<4) throw std::runtime_error("No enough arguments for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
    if(resource.args.size()>4) throw std::runtime_error("Too many arguments for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
    for(auto& arg:resource.args){
        try{
            std::stof(arg);
        }
        catch(const std::exception& e){
            throw std::runtime_error("Invalid argument for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line) + "\nArgument: " + arg);
        }
    }
    entity->AddComponent<AmbientLightComponent>(glm::vec4(std::stof(resource.args[0]),std::stof(resource.args[1]),std::stof(resource.args[2]),std::stof(resource.args[3])));
}
void SceneLoader::LightComp(Entity *entity, ParsedResource &resource, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets, ScriptManager &scriptmanager, Input *input, Camera &camera){
    if(resource.args.size()<5) throw std::runtime_error("No enough arguments for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
    if(resource.args.size()>5) throw std::runtime_error("Too many arguments for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
    for(auto& arg:resource.args){
        try{
            std::stof(arg);
        }
        catch(const std::exception& e){
            throw std::runtime_error("Invalid argument for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line) + "\nArgument: " + arg);
        }
    }
    entity->AddComponent<LightComponent>(glm::vec4(std::stof(resource.args[0]),std::stof(resource.args[1]),std::stof(resource.args[2]),std::stof(resource.args[3])),std::stof(resource.args[4]));
}
void SceneLoader::ScriptComp(Entity *entity, ParsedResource &resource, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets, ScriptManager &scriptmanager, Input *input, Camera &camera){
    if(resource.args.size()<1) throw std::runtime_error("No enough arguments for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
    if(resource.args.size()>1) throw std::runtime_error("Too many arguments for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
    try{
    auto* component = entity->AddComponent<ScriptComponent>(scriptmanager.CreateScript(resource.args[0]));
    component->SetEntity(entity);
    component->SetInput(input);
    }
    catch(const std::exception& e){
        throw std::runtime_error("Invalid argument for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line) + "\nArgument: " + resource.args[0]);
    }
}
void SceneLoader::CameraComp(Entity *entity, ParsedResource &resource, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets, ScriptManager &scriptmanager, Input *input, Camera &camera){
    if(resource.args.size()<1) throw std::runtime_error("No enough arguments for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
    if(resource.args.size()>1) throw std::runtime_error("Too many arguments for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
    auto it = ids.find(resource.args[0]);
    if(it==ids.end())
    throw std::runtime_error("Invalid argument for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line) + "\nArgument: " + resource.args[0]);
    uint64_t targetid = it->second;
    // std::cout << "SceneLoader::CameraComp: Camera pointer: " << &camera << "\n";
    auto* component = entity->AddComponent<CameraComponent>(&camera,currentscene.get()->FindEntity(targetid));
    
}
void SceneLoader::CreateScene(Entity *entity, ParsedResource &resource, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets, ScriptManager &scriptmanager, Input *input, Camera &camera){
    currentscene = std::make_unique<Scene>(resource.name);
}
void SceneLoader::CreateEntity(Entity *entity, ParsedResource &resource, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets, ScriptManager &scriptmanager, Input *input, Camera &camera){
    currentID = currentscene->AddEntity(resource.name);
    ids.emplace(resource.name,currentID);
}
   
void SceneLoader::AddComponent(Entity *entity, ParsedResource &resource, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets, ScriptManager &scriptmanager, Input *input, Camera &camera){
    if(resource.name.empty()) throw std::runtime_error("No enough arguments for " + resource.type + "\n" + resource.file + " - " +std::to_string(resource.line));
    if(!currentID)
    throw std::runtime_error("No Entity found: " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
    auto* entitya = currentscene->FindEntity(currentID);
    auto it = commands.find(resource.name.c_str());
    if(it == commands.end()) {
        // std::cout << "Unknown component type: "  << resource.name << "\n"<< resource.file << " - " << resource.line << "\n";
        throw std::runtime_error("Unknown component type: " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
        return;
    }
    it->second(entitya,resource,assets,scriptmanager,input,camera);
}
    
void SceneLoader::EntityInit(Entity *entity, ParsedResource &resource, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets, ScriptManager &scriptmanager, Input *input, Camera &camera){
    if(!currentID) 
    throw std::runtime_error("No Entity found: " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
        
    currentscene->FindEntity(currentID)->init();
}

void SceneLoader::AddAnimation(Entity *entity, ParsedResource &resource, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets, ScriptManager &scriptmanager, Input *input, Camera &camera){
    if(!currentID)
    throw std::runtime_error("No Entity found: " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
    if(resource.args.size()<1) throw std::runtime_error("No enough arguments for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
    if(resource.args.size()>1) throw std::runtime_error("To many arguments for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
    auto* animationcomp = currentscene->FindEntity(currentID)->GetComponent<AnimationComponent>();
    auto it = assets.find(resource.args[0]);
    if(it==assets.end()) {
        throw std::runtime_error("Asset not found: " + resource.args[0] + "\n" + resource.file + " - " +std::to_string(resource.line));
        return;
    }
    auto& handle = *static_cast<AssetHandle<Animation>*>(it->second.get());
    animationcomp->AddAnimation(resource.name,handle);
}