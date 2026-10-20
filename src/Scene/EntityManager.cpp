//EntityManager.cpp
#include "Scene/EntityManager.h"
#include "Core/EntityID.h"
#include <iostream>

std::uint64_t EntityManager::CreateEntity(const std::string& name) {
    EntityID id(Nextid++);//Sürekli olarak 1 arttıracak 
    uint64_t ID = id.Value();
    uint64_t uuID = uuid.GetID();

    auto entity = std::make_unique<Entity>(ID,uuID,name);

    // entities.push_back(std::move(entity));
    entities.insert({ID,std::move(entity)});
    std::set<uint64_t> map = uuid.GetAll();
    // std::cout << "------------\nCurrent UUID map:\n";
    // for(auto&x : map){
    //     std::cout << x <<"\n";
    // }
    // std::cout << "------------\n";
    return ID;

}
void EntityManager::DestroyEntity(std::uint64_t id){

    // for(auto it = entities.begin();it!=entities.end();it++){

    //     if(id == (*it)->GetID()){
    //         entities.erase(it);
    //         return;
    //     }
    // }
    
    // std::set<uint64_t> map = uuid.GetAll();
    // std::cout << "------------\nCurrent UUID map:\n";
    // for(auto&x : map){
    //     std::cout << x <<"\n";
    // }
    // std::cout << "------------\n";
    auto it = entities.find(id);
    if(it!=entities.end()){
        if(it->second->IsDestroy()) return;
        it->second->DestroyerMark();
        destroy_queue.push(id);
    }
}

Entity* EntityManager::FindEntity(std::uint64_t id){
    // for(auto& entity:entities){

    //     if(entity->GetID() == id) return entity.get();
        
    // }
    auto entity = entities.find(id);
    if(entity != entities.end())return entity->second.get();
    return nullptr;
}
const std::unordered_map<uint64_t,std::unique_ptr<Entity>>& EntityManager::GetEntites() const{
    return entities;
}
const unsigned int EntityManager::GetSize() const{
    return entities.size();
}
void EntityManager::UpdateEntities(float dt,float x,float y,float max_r){
    
    for(auto& [id,entity]: GetEntites()){
        bool a = entity->GetName() == "Player";
        if(entity->GetType() & static_cast<uint32_t>(CopmonentCategory::Transform)){
            glm::vec2 tr = entity->GetComponent<TransformComp>()->position;
            // if(a){
            // std::cout << entity->GetName() << " Tr: "<<tr.x << "," <<tr.y <<"\t";
            // std::cout << entity->GetName() << " Cam: "<<x << "," <<y <<"\t";
            // std::cout << entity->GetName() << " Cam max: "<<max_r <<"\t";
            // std::cout << entity->GetName() << " Diff: "<<std::abs(tr.x-x) << "," <<std::abs(tr.y-y) <<"\n";
            // }
            if(std::abs(tr.x-x)>max_r || std::abs(tr.y-y)>max_r){continue;}
        }
        // if(a)std::cout << entity->GetName() << " Updated\n";
        entity->UpdateComponents(dt);
    }
    PendingDestroy();
}
void EntityManager::UpdateAnimations(float deltatime,float x,float y,float max_r, ResourceManagerPlus *resoursmanager){
    for(auto& [id,entity]: GetEntites()){
        if(!(entity->GetType() & static_cast<uint32_t>(CopmonentCategory::Animation)))continue;
        if(entity->GetType() & static_cast<uint32_t>(CopmonentCategory::Transform)){
            glm::vec2 tr = entity->GetComponent<TransformComp>()->position;
            if(std::abs(tr.x-x)>max_r || std::abs(tr.y-y)>max_r) continue;
        }
        entity->UpdateAnimations(deltatime,resoursmanager);
    }
}
void EntityManager::EventEntities(Event &event,float x,float y,float max_r){
    for(auto& [id,entity]: GetEntites()){
        if(entity->GetType() & static_cast<uint32_t>(CopmonentCategory::Transform)){
            glm::vec2 tr = entity->GetComponent<TransformComp>()->position;
            if(std::abs(tr.x-x)>max_r || std::abs(tr.y-y)>max_r) continue;
        }
        entity->OnEvent(event);
    }
}

void EntityManager::PendingDestroy(){
    for(;!destroy_queue.empty();destroy_queue.pop()){
        auto it = entities.find(destroy_queue.top());
        if (it == entities.end()) continue;
        
        auto euuid = (*it->second).GetUUID();
        uuid.RemoveID(euuid);
        it->second->OnDestroy();
        entities.erase(it);
    }
}