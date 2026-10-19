//Entity.cpp
#include "Scene/Entity.h"
#include <iostream>
#include <cstdint>

Entity::Entity(std::uint64_t id,std::uint64_t uuid,std::string name): id(id),uuid(uuid),name(name)
{
    // std::cout << "Entity has created\n";
    // std::cout << "|->name: " << name << "\n";
    // std::cout << "|->ID: " << id <<"\n";
    // std::cout << "|->UUID: " <<uuid <<"\n";
}
Entity::~Entity(){
    OnDestroy();
    // std::cout << "Entity has destroyed\n";
    // std::cout << "|->name: " << name << "\n";
    // std::cout << "|->ID: " << id <<"\n";
    // std::cout << "|->UUID: " <<uuid <<"\n";
    
}

std::uint64_t Entity::GetID() const
{
    return id;
}
std::uint64_t Entity::GetUUID() const
{
    return uuid;
}
std::string Entity::GetName() const
{
    return name;
}
Scene *Entity::GetScene() const
{
    return scene;
}
std::uint32_t Entity::GetType() const{
    return componenttypes;
}


void Entity::ListComponents() const{
    std::cout << "Components:\n";
    for(auto& component:components){
        if(component == nullptr) continue;
        std::cout << "|->" << component.get() <<"\n";
    }
}

void Entity::UpdateComponents(float dt){
    if(pendingDestroy||!inited) return;
    for(auto& component: components){
        if(component == nullptr) continue;
        component->Update(dt);
    }
}
void Entity::UpdateAnimations(float dt,ResourceManagerPlus *resoursmanager){
    if(pendingDestroy||!inited) return;
    for(auto& component: components){
        if(component == nullptr) continue;
        component->AnimationUpdate(dt,resoursmanager);
    }
}

void Entity::OnEvent(Event &event){
    if(pendingDestroy||!inited) return;
    for(auto& component: components){
        if(component == nullptr) continue;
        component->OnEvent(event);
    }
}


void Entity::init(Scene *scene){
    if(inited||pendingDestroy) return;
    inited = true;
    this->scene = scene;
    for(auto& component:components){
        if(component == nullptr) continue;
        component->AddOwner(this);
        component->OnCreate();
        componenttypes |= static_cast<uint32_t>(component->GetCategory());
    }
}

bool Entity::IsDestroy(){
    return pendingDestroy;
}
void Entity::OnDestroy(){
    for(auto& component: components){
        if(component == nullptr) continue;
        component->OnDestroy();
    }
}
void Entity::DestroyerMark(){
    pendingDestroy = true;
}