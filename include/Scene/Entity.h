//Entity.h
#pragma once
#include "Core/UUID.h"
#include "Event/Event.h"
#include "Scene/Components/Component.h"
#include "Scene/Components/MeshComponent.h"
#include "Scene/Components/TransformComponent.h"
#include "Scene/Components/SpriteComponent.h"
#include "Scene/Components/MaterialComponent.h"
#include "Scene/Components/ScriptComponent.h"
#include "Scene/Components/RendererComponent.h"
#include "Scene/Components/AnimationComponent.h"
#include "Scene/Components/LightComponent.h"
#include "Scene/Components/AmbientLightComponent.h"
#include "Scene/Components/CameraComponent.h"

#include <string>
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <iostream>

class Entity
{
private:
    std::uint64_t id;
    std::uint64_t uuid;
    std::string name;
    std::unordered_map<std::type_index, std::unique_ptr<Component>> components;
    bool inited = false;
    bool pendingDestroy = false;
public:
    Entity(std::uint64_t id,std::uint64_t uuid,std::string name);
    ~Entity();
    std::uint64_t   GetID()     const;
    std::uint64_t   GetUUID()   const;
    std::string     GetName()   const;

    void init();
    void OnDestroy();
    bool IsDestroy();
    void DestroyerMark();
    template <typename C, typename... Args> C*    AddComponent     (Args&&... args);
    template <typename C> bool  HasComponent     ();
    template <typename C> C*    GetComponent     ();
    template <typename C> void  RemoveComponent  ();
    void UpdateComponents(float dt);
    void UpdateAnimations(float dt,ResourceManagerPlus* resoursmanager);
    void ListComponents  () const;
    void OnEvent         (Event& event);
    
};

#include "Scene/Entity.inl"
