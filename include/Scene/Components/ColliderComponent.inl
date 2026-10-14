//ColliderComponent.inl
#pragma once

template<class T,typename... Args> void ColliderComponent::AddCollider(Args&&... args){
    
    std::unique_ptr<T> collider = std::make_unique<T>(std::forward<Args>(args)...);

    colliders.push_back({std::move(collider),glm::vec4(0.15f,0.4f,0.8f,1.0f),true});
}