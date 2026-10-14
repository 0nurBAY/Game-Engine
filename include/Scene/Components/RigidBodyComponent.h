//RigidBodyComponent.h

#pragma once

#include "Scene/Components/Component.h"
#include "Physics/Physictypes.h"
#include <glm/glm.hpp>

class RigidBodyComponent: public Component{
private:
    float mass;
    glm::vec2 velocity = glm::vec2(0.0f);
    glm::vec2 acceleration = glm::vec2(0.0f);
    glm::vec2 forces = glm::vec2(0.0f);
    BodyType type;
    bool ApplyGravity = false;
    float GravityScale = 0.0f;
public:
    RigidBodyComponent(float mass,BodyType type,bool ApplyGravity,float GravityScale);

    void ApplyForce(glm::vec2 force);
    void SetVelocity(glm::vec2 velocity);
    void AddVelocity(glm::vec2 velocity);
    void UpdateRigidBody(float dt) override;

    glm::vec2 GetVelocity() const;
    CopmonentCategory GetCategory() const override;


};