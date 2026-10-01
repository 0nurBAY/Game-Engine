//ColliderComponent.cpp

#include "Scene/Components/ColliderComponent.h"
#include "Event/Events.h"
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

void ColliderComponent::EnableCollider(size_t index, bool enable){
    if(index < colliders.size()){
        colliders[index].enable = enable;
    }
}

void ColliderComponent::EnableCollider(bool enable){
    for(auto& collider: colliders){
        collider.enable = enable;
    }
}

// void ColliderComponent::OnEvent(Event &event){
//     EventDispatcher dispatcher(event);
//     dispatcher.Dispatcher<
// }