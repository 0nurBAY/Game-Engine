//PhysicEvents.h

#pragma once

#include "Event/Event.h"
#include <glm/glm.hpp>
#include <iostream>

class Entity;

class PhysicsEntityAddEvent : public Event
{
private:
    Entity* entity;
public:
    PhysicsEntityAddEvent(Entity* entity):entity(entity){}
    Entity* GetEntity() const { return entity; }
    EventType GetType() const override{
       return EventType::PhysicsEntityAdd;
    }
    static EventType StaticGetType() {
     return EventType::PhysicsEntityAdd;
    }
    int GetCategoryFlags() const override{
       return static_cast<int>(EventCategory::Input)|static_cast<int>(EventCategory::Application)|static_cast<int>(EventCategory::Physic);
   }
};

class PhysicsEntityRemoveEvent : public Event
{
private:
    Entity* entity;
public:
    PhysicsEntityRemoveEvent(Entity* entity):entity(entity){}
    Entity* GetEntity() const { return entity; }
    EventType GetType() const override{
       return EventType::PhysicsEntityRemove;
    }
    static EventType StaticGetType() {
     return EventType::PhysicsEntityRemove;
    }
    int GetCategoryFlags() const override{
       return static_cast<int>(EventCategory::Input)|static_cast<int>(EventCategory::Application)|static_cast<int>(EventCategory::Physic);
   }
};

class CollisionEvent : public Event
{
private:
    Entity* other;
    glm::vec2 dir;
public:
    CollisionEvent(Entity* other,glm::vec2 dir):other(other),dir(dir){}
    Entity* GetOther() const {return other;}
    glm::vec2 GetDir() const {return dir;}
    EventType GetType() const override{
       return EventType::OnCollision;
    }
    static EventType StaticGetType() {
     return EventType::OnCollision;
    }
    int GetCategoryFlags() const override{
       return static_cast<int>(EventCategory::Input)|static_cast<int>(EventCategory::Application)|static_cast<int>(EventCategory::Physic);
   }
};