//RigidBodyComponent.cpp

#include "Scene/Components/RigidBodyComponent.h"
#include "Renderer/DebugRenderer.h"
#include "Scene/Entity.h"
#include "Scene/Scene.h"

RigidBodyComponent::RigidBodyComponent(float mass,BodyType type,float restution, bool ApplyGravity, float GravityScale):
mass(mass),
type(type),
restution(restution),
ApplyGravity(ApplyGravity),
GravityScale(GravityScale)
{}

void RigidBodyComponent::ApplyForce(glm::vec2 force){
    if(sleep)  Wake();
    // std::cout << "Force Apllied: [" << force.x << "," << force.y <<"]Newton\n";
    forces += force;
    // std::cout << "Current Force: [" << force.x << "," << force.y <<"]Newton\n";
}
void RigidBodyComponent::SetForce(glm::vec2 force){
    if(sleep)  Wake();
    forces = force;
}
void RigidBodyComponent::SetCorrection(glm::vec2 force){
    applied_correction = force;
}
void RigidBodyComponent::ResetCorrection(){
    applied_correction = glm::vec2(0.0f);
}
void RigidBodyComponent::SetVelocity(glm::vec2 velocity){
    if(sleep)  Wake();
    this->velocity = velocity;
}
void RigidBodyComponent::AddVelocity(glm::vec2 velocity){
    if(sleep)  Wake();
    this->velocity += velocity;
}
void RigidBodyComponent::AddCorrection(glm::vec2 force){
    this->applied_correction += force;
}
void RigidBodyComponent::UpdateRigidBody(float dt){
    if(sleep) return;
    if(type == BodyType::Static) return;
    if(mass == 0) return;
    if(ApplyGravity) forces += glm::vec2(0.0f,-GravityScale*mass);
    acceleration = forces/mass;
    velocity += acceleration*dt;
    velocity_value = glm::dot(velocity,velocity);
    if(velocity_value < sleepspd) sleeptimer += dt;
    else sleeptimer = 0;
    if(sleeptimer > 0.5f && !(glm::dot(applied_correction,applied_correction))){
        sleeptimer = 0.0f;
        sleep = true; 
        velocity = glm::vec2(0.0f);
        forces = glm::vec2(0.0f);
        preforces = glm::vec2(0.0f);
        return;}
    preforces = forces;
    forces = glm::vec2(0.0f);
    // DebugRenderer* debugrenderer = owner->GetScene()->GetDebugRenderer();
    // debugrenderer->DrawLine(owner->GetComponent<TransformComp>()->position,owner->GetComponent<TransformComp>()->position+glm::vec2(preforces.x,0.0f),glm::vec4(0.4f,0.5f,0.8f,1.0f));
    // debugrenderer->DrawLine(owner->GetComponent<TransformComp>()->position,owner->GetComponent<TransformComp>()->position+glm::vec2(0.0f,preforces.y),glm::vec4(0.4f,0.5f,0.8f,1.0f));

    // debugrenderer->DrawLine(owner->GetComponent<TransformComp>()->position,owner->GetComponent<TransformComp>()->position+glm::vec2(velocity.x,0.0f),glm::vec4(0.13f,0.8f,0.3f,1.0f));
    // debugrenderer->DrawLine(owner->GetComponent<TransformComp>()->position,owner->GetComponent<TransformComp>()->position+glm::vec2(0.0f,velocity.y),glm::vec4(0.13f,0.8f,0.3f,1.0f));

}
void RigidBodyComponent::Wake(){
    sleep = false;
    sleeptimer = 0.0f;
}
glm::vec2 RigidBodyComponent::GetVelocity() const{
    return velocity;
}
glm::vec2 RigidBodyComponent::GetForces() const{
    return preforces;
}
glm::vec2 RigidBodyComponent::GetCorrection() const{
    return applied_correction;
}
float RigidBodyComponent::GetMass() const{
    return mass;
}
float RigidBodyComponent::GetInvMass() const{
    
    return (type==BodyType::Static||mass == 0)? 0:1/mass;
}
float RigidBodyComponent::GetRestitution() const{
    return restution;
}
bool RigidBodyComponent::IsMoving() const{
    return !sleep;
}
bool RigidBodyComponent::IsSleeping() const{
    return sleep;
}
bool RigidBodyComponent::IsStatic() const{
    return type==BodyType::Static;
}


CopmonentCategory RigidBodyComponent::GetCategory() const{
    return (CopmonentCategory::Physic);
}

BodyType RigidBodyComponent::GetBodyType() const{
    return type;
}