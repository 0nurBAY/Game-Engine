//Component.h
#pragma once
#include "Event/Event.h"
#include "Resource/ResourceManagerplus.h"
class Entity;

class Component
{
public:
    virtual ~Component();
    virtual void AddOwner(Entity* own);
    virtual void AnimationUpdate(float dt,ResourceManagerPlus* resourceManager) {};
    virtual void Update(float dt) {};
    virtual void OnEvent  (Event& event) {};
    virtual void OnCreate () {};
    virtual void OnDestroy() {};
protected:
    Entity* owner = nullptr;
};
