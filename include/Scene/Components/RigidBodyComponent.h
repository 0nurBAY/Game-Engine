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
    glm::vec2 applied_correction = glm::vec2(0.0f);
    glm::vec2 preforces = glm::vec2(0.0f);
    BodyType type;
    float restution;
    bool ApplyGravity = false;
    float GravityScale = 0.0f;
public:
    RigidBodyComponent(float mass,BodyType type,float restution,bool ApplyGravity,float GravityScale);

    void SetForce(glm::vec2 force);
    void SetVelocity(glm::vec2 velocity);
    void SetCorrection(glm::vec2 force);
    void ResetCorrection();

    void ApplyForce(glm::vec2 force);
    void AddVelocity(glm::vec2 velocity);
    void AddCorrection(glm::vec2 force);

    void UpdateRigidBody(float dt) override;

    glm::vec2 GetVelocity() const;
    glm::vec2 GetForces() const;
    glm::vec2 GetCorrection() const;
    bool IsMoving() const;
    float GetMass() const;
    float GetInvMass() const;
    float GetRestitution() const;
    CopmonentCategory GetCategory() const override;
    BodyType GetBodyType() const;


};