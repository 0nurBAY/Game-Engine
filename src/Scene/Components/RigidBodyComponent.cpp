//RigidBodyComponent.cpp

#include "Scene/Components/RigidBodyComponent.h"

RigidBodyComponent::RigidBodyComponent(float mass,BodyType type, bool ApplyGravity, float GravityScale):
mass(mass),
type(type),
ApplyGravity(ApplyGravity),
GravityScale(GravityScale)
{}

void RigidBodyComponent::ApplyForce(glm::vec2 force){
    forces += force;
}

void RigidBodyComponent::SetVelocity(glm::vec2 velocity){
    this->velocity = velocity;
}

void RigidBodyComponent::AddVelocity(glm::vec2 velocity){
    this->velocity += velocity;
}
void RigidBodyComponent::UpdateRigidBody(float dt){
    if(type == BodyType::Static) return;
    if(mass == 0) return;
    if(ApplyGravity) forces += glm::vec2(0.0f,-GravityScale*mass);
    acceleration = forces/mass;
    velocity += acceleration*dt;
    forces = glm::vec2(0.0f);
}

glm::vec2 RigidBodyComponent::GetVelocity() const{
    return velocity;
}








CopmonentCategory RigidBodyComponent::GetCategory() const{
    return (CopmonentCategory::Physic);
}

