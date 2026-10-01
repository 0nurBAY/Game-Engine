//ColliderComponent.h
#pragma once
#include "Scene/Components/Component.h"
#include "Physics/ColliderShape.h"
#include <vector>
#include <memory>
struct ColliderData{
    std::unique_ptr<ColliderShape> collider;
    bool enable;
};

class ColliderComponent: public Component
{
private:
    std::vector<ColliderData> colliders;
public:
    ColliderComponent();
    void EnableCollider(size_t index, bool enable);
    void EnableCollider(bool enable);
    // void OnEvent(Event& event) override;
    CopmonentCategory GetCategory() const override;
    template<typename T ,typename... Args> void AddCollider(Args&&... args);
    std::vector<ColliderShape*> Getcolliders();
};

#include "Scene/Components/ColliderComponent.inl"