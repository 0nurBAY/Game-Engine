//ColliderComponent.h
#pragma once
#include "Scene/Components/Component.h"
#include "Physics/ColliderShape.h"
#include <vector>
#include <memory>
#include <glm/vec4.hpp>
struct ColliderData{
    std::unique_ptr<ColliderShape> collider;
    glm::vec4 color;
    bool enable;
};

class ColliderComponent: public Component
{
private:
    std::vector<ColliderData> colliders;
public:
    ColliderComponent   ();
    void EnableCollider (size_t index);
    void EnableCollider ();
    void DisableCollider(size_t index);
    void DisableCollider();
    
    void SetColliderColor(size_t index, glm::vec4 color);
    void SetColliderColor(glm::vec4 color);

    
    void ColliderColorDefault(size_t index);
    void ColliderColorDefault();
    // void OnEvent(Event& event) override;
    CopmonentCategory GetCategory() const override;
    void Update(float dt) override;
    template<typename T ,typename... Args> void AddCollider(Args&&... args);
    std::vector<ColliderShape*> Getcolliders();
};

#include "Scene/Components/ColliderComponent.inl"