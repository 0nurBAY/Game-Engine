//Component.h
#pragma once
#include "Event/Event.h"
#include "Resource/ResourceManagerplus.h"
#include "Scene/Components/ComponentCategory.h"
class Entity;

class Component
{
public:
    virtual ~Component();
    virtual void AddOwner(Entity* own);
    virtual void Update(float dt) {};
    virtual void AnimationUpdate(float dt,ResourceManagerPlus* resourceManager) {};
    virtual void UpdateRigidBody(float dt) {};
    virtual void OnEvent  (Event& event) {};
    virtual void OnCreate () {};
    virtual void OnDestroy() {};
    virtual CopmonentCategory GetCategory() const = 0;
protected:
    Entity* owner = nullptr;
};
