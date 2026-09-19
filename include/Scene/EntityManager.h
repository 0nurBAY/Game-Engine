//EntityManager.h
#pragma once
#include "Scene/Entity.h"
#include "Core/UUID.h"
#include <unordered_map>
#include <memory>
#include <string>
#include <stack>

class EntityManager
{
private:
    uint32_t Nextid = 1;
    UUID uuid;
    std::unordered_map<uint64_t,std::unique_ptr<Entity>> entities; 
    std::stack<uint64_t> destroy_queue;
public:
    uint64_t        CreateEntity    (const std::string& name);
    void            PendingDestroy  ();
    void            DestroyEntity   (uint64_t id);
    Entity*         FindEntity      (uint64_t id);
    void            UpdateEntities  (float dt);
    void            UpdateAnimations(float deltatime, ResourceManagerPlus* resoursmanager);
    void            EventEntities   (Event& event);
    const unsigned int GetSize() const;
    const std::unordered_map<uint64_t,std::unique_ptr<Entity>>& GetEntites() const;
};
