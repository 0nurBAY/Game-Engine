//Sceneloader.cpp

#include "Core/SceneLoader.h"
#include "Core/AssetLoader.h"
#include <glm/glm.hpp>
#include <stdexcept>
#include <fstream>
#include <sstream>
void SceneLoader::Init(){
    substitute.emplace("NAME",0);
    substitute.emplace("XPOS",1);
    substitute.emplace("YPOS",2);
    commands.emplace("SCENE",       [this](Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera){CreateScene(entity,resource,assets,scriptmanager,input,camera);});
    commands.emplace("ENTITY",      [this](Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera){CreateEntity(entity,resource,assets,scriptmanager,input,camera);});
    commands.emplace("COMPONENT",   [this](Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera){AddComponent(entity,resource,assets,scriptmanager,input,camera);});
    commands.emplace("ADDANIMATION",[this](Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera){AddAnimation(entity,resource,assets,scriptmanager,input,camera);});
    commands.emplace("ENTITYINIT",  [this](Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera){EntityInit(entity,resource,assets,scriptmanager,input,camera);});
    commands.emplace("IMPORT",      [this](Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera){Import(entity,resource,assets,scriptmanager,input,camera);});

    commands.emplace("Transform",   [this](Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera){this->TransformComponent(entity,resource,assets,scriptmanager,input,camera);});
    commands.emplace("Material",    [this](Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera){this->MaterialComp(entity,resource,assets,scriptmanager,input,camera);});
    commands.emplace("Renderer",    [this](Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera){this->RendererComp(entity,resource,assets,scriptmanager,input,camera);});
    commands.emplace("Sprite",      [this](Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera){this->SpriteComp(entity,resource,assets,scriptmanager,input,camera);});
    commands.emplace("Animation",   [this](Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera){this->AnimationComp(entity,resource,assets,scriptmanager,input,camera);});
    commands.emplace("Ambient",     [this](Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera){this->AmbientComp(entity,resource,assets,scriptmanager,input,camera);});
    commands.emplace("Light",       [this](Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera){this->LightComp(entity,resource,assets,scriptmanager,input,camera);});
    commands.emplace("Script",      [this](Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera){this->ScriptComp(entity,resource,assets,scriptmanager,input,camera);});
    commands.emplace("Camera",      [this](Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera){this->CameraComp(entity,resource,assets,scriptmanager,input,camera);});
    commands.emplace("Drag",        [this](Entity* entity,ParsedResource& resource,std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager& scriptmanager,Input* input,Camera& camera){this->DragComp(entity,resource,assets,scriptmanager,input,camera);});

}
void SceneLoader::LoadScene(ParsedResource &resource, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets,ScriptManager &scriptmanager,Input *input,Camera &camera){
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
    entity->AddComponent<AnimationComponent>();
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
    entity->AddComponent<CameraComponent>(&camera,currentscene.get()->FindEntity(targetid));
    
}
void SceneLoader::DragComp(Entity *entity, ParsedResource &resource, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets, ScriptManager &scriptmanager, Input *input, Camera &camera){
    if(resource.args.size()>0) throw std::runtime_error("Too many arguments for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
    entity->AddComponent<DragComponent>();

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
void SceneLoader::EntityInit(Entity *entity, ParsedResource &resource, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets, ScriptManager &scriptmanager, Input *input, Camera &camera){
    if(!currentID) 
    throw std::runtime_error("No Entity found: " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
        
    currentscene->FindEntity(currentID)->init(currentscene.get());
}

void SceneLoader::Import(Entity *entity, ParsedResource &resource, std::unordered_map<std::string, std::unique_ptr<AssetHandleBase>> &assets, ScriptManager &scriptmanager, Input *input, Camera &camera){
    int line_num = currentline;
    currentline = 0;
    if(resource.args.size()<3) throw std::runtime_error("No enough arguments for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
    if(resource.args.size()>3) throw std::runtime_error("To many arguments for " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
    std::ifstream importfile("resources/" + resource.name);
    if(!importfile.is_open()) throw std::runtime_error("Failed to open import file: " + resource.name + "\n" + resource.file + " - " +std::to_string(resource.line));
    std::string line;
    while(std::getline(importfile,line)){
        if(line.empty() || line[0]=='#') {
            currentline++;
            continue;
        }
        try{
            line = SubstituteArgs(line,resource.args);
        }
        catch(const std::exception& e){
            throw std::runtime_error("Error processing line: " + line + "\n" + e.what());
        }
        std::stringstream ss(line);
        ParsedResource resource2;
        resource2.file = resource.name;
        ss >> resource2.type;
        ss >> resource2.name;
        std::string args;
        while(ss >> args){
            resource2.args.push_back(args);
        }
        LoadScene(resource2,assets,scriptmanager,input,camera);

    }
    currentline = line_num;
}
std::string SceneLoader::SubstituteArgs(std::string line, std::vector<std::string> args){
    try{
        std::stof(args[1]);
        std::stof(args[2]);
    }
    catch(const std::exception& e){
        throw std::runtime_error("Error substituting arguments in line: " + line + "\n" + e.what());
    }

    while(true){
        size_t start=0;
        size_t last =0;
        start = line.find("{",last);
        if(start==std::string::npos) break;
        last = line.find("}",start);
        if(last==std::string::npos) throw std::runtime_error("Unmatched { in line: " + line);
        std::string key = line.substr(start+1,last-start-1);
        auto it = substitute.find(key);
        if(it==substitute.end()) throw std::runtime_error("Unknown substitution key: " + key + " in line: " + line);
        line.replace(start,last-start+1,args[it->second]);
    }
    std::cout << "Importing line: " << line << "\n";

    return line;
}
