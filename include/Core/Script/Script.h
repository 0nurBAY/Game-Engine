//Script.h
#pragma once
#include "Resource/ResourceManagerPlus.h"
class Entity;
class Input;
class Event;
class Script
{
private:
    Entity* entity  = nullptr;
    Input* input    = nullptr;  
public:
    virtual ~Script() = default;
    void SetEntity  (Entity* entity);
    void SetInput   (Input* input);
    
    virtual void OnCreate   ()               {};
    virtual void Update     (float deltatime){};
    virtual void OnEvent    (Event& event)   {};
    virtual void OnDestroy  ()               {};

    Entity* GetEntity() const;
    Input*  GetInput() const;

};
