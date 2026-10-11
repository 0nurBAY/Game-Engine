//RigidBodyComponent.h
#include "Scene/Components/Component.h"
#include <glm/glm.hpp>

enum class BodyType{
    Dynamic,
    Static,
    Kinematic
};

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
    void UpdateRigidBody(float dt) override;

    glm::vec2 GetVelocity() const;
    CopmonentCategory GetCategory() const override;


};