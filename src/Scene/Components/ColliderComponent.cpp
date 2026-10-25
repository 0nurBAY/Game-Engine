//ColliderComponent.cpp

#include "Scene/Components/ColliderComponent.h"
#include "Physics/HitBoxDebuger.h"
#include "Event/Events.h"
#include "Scene/Scene.h"
#include "Renderer/Camera.h"

#include <iostream>
ColliderComponent::ColliderComponent(){}

CopmonentCategory ColliderComponent::GetCategory() const{
    return (CopmonentCategory::Physic);
}

std::vector<ColliderShape*> ColliderComponent::Getcolliders(){
    std::vector<ColliderShape*> resault;
    for (auto& collider: colliders){
        if(collider.enable) resault.push_back(collider.collider.get());
    }
    return resault;
}


void ColliderComponent::EnableCollider(size_t index){
    if(index < colliders.size()){
        colliders[index].enable = true;
    }
}
void ColliderComponent::EnableCollider(){
    for(auto& collider: colliders){
        collider.enable = true;
    }
}

void ColliderComponent::DisableCollider(size_t index){
    if(index < colliders.size()){
        colliders[index].enable = false;
    }
}
void ColliderComponent::DisableCollider(){
    for(auto& collider: colliders){
        collider.enable = false;
    }
}



void ColliderComponent::SetColliderColor(size_t index, glm::vec4 color){
    if(index < colliders.size()){
        colliders[index].color = color;
    }
}
void ColliderComponent::SetColliderColor(glm::vec4 color){
    for(auto& collider: colliders){
        collider.color = color;
    }
}



void ColliderComponent::ColliderColorDefault(size_t index){
    if(index < colliders.size()){
        colliders[index].color = glm::vec4(0.15f,0.4f,0.8f,1.0f);
    }
}
void ColliderComponent::ColliderColorDefault(){
    for(auto& collider: colliders){
        collider.color = glm::vec4(0.15f,0.4f,0.8f,1.0f);
    }
}



void ColliderComponent::Update(float dt){
    // std::cout <<"--------------------\nColliderComponent::Update\n";
    // DebugRenderer* debugrenderer = owner->GetScene()->GetDebugRenderer();
    // for(auto& shape: colliders){
    //     // std::cout <<"Collider: "<<shape.collider.get() << "State:\t";
    //     if(shape.enable){
    //         // std::cout <<"Enable\n";
    //         HitBoxDebug::DrawHitBox(shape.collider.get(),owner,shape.color,debugrenderer);
    //     }
    // }
}
// void ColliderComponent::OnEvent(Event &event){
//     EventDispatcher dispatcher(event);
//     dispatcher.Dispatcher<
// }