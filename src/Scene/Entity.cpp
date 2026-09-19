//Entity.cpp
#include "Scene/Entity.h"
#include <iostream>
#include <cstdint>

Entity::Entity(std::uint64_t id,std::uint64_t uuid,std::string name): id(id),uuid(uuid),name(name)
{
    std::cout << "Entity has created\n";
    std::cout << "|->name: " << name << "\n";
    std::cout << "|->ID: " << id <<"\n";
    std::cout << "|->UUID: " <<uuid <<"\n";
}
Entity::~Entity(){
    std::cout << "Entity has destroyed\n";
    std::cout << "|->name: " << name << "\n";
    std::cout << "|->ID: " << id <<"\n";
    std::cout << "|->UUID: " <<uuid <<"\n";
    
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

void Entity::ListComponents() const{
    std::cout << "Components:\n";
    for(auto& map:components){
        std::cout << "|->" << map.first.name() <<"\n";
    }
}

void Entity::UpdateComponents(float dt){
    if(pendingDestroy||!inited) return;
    for(auto& component: components){
        component.second->Update(dt);
    }
}
void Entity::UpdateAnimations(float dt,ResourceManagerPlus *resoursmanager){
    if(pendingDestroy||!inited) return;
    for(auto& component: components){
        component.second->AnimationUpdate(dt,resoursmanager);
    }
}

void Entity::OnEvent(Event &event){
    if(pendingDestroy||!inited) return;
    for(auto& component: components){
        component.second->OnEvent(event);
    }
}


void Entity::init(){
    if(inited||pendingDestroy) return;
    inited = true;
    for(auto& map:components){
        map.second->OnCreate();
    }

}
bool Entity::IsDestroy(){
    return pendingDestroy;
}
void Entity::OnDestroy(){
    for(auto& component: components){
        component.second->OnDestroy();
    }
}
void Entity::DestroyerMark(){
    pendingDestroy = true;
}