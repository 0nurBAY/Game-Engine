//CollisionSolver.cpp

#include "Physics/CollisionSolver.h"
#include "Renderer/DebugRenderer.h"
#include "Scene/Scene.h"
#include "Scene/Entity.h"
void CollisionSolver::StaticVsDynamic(ColliderResult *collision,bool reverse){
    Entity* entityA;
    Entity* entityB;
    glm::vec2 normal;
    if(reverse){
        entityB = collision->entityA;
        entityA = collision->entityB;
        normal = -collision->normal;
    }else{
        entityA = collision->entityA;
        entityB = collision->entityB;
        normal = collision->normal;
    }
    auto* transformA = entityA->GetComponent<TransformComp>();
    auto* transformB = entityB->GetComponent<TransformComp>();
    auto* rigidBodyA = entityA->GetComponent<RigidBodyComponent>();
    auto* rigidBodyB = entityB->GetComponent<RigidBodyComponent>();
    float r_massA = 1/(rigidBodyA->GetMass());
    float r_massB = 1/(rigidBodyB->GetMass());
    glm::vec2 velocity = rigidBodyA->GetVelocity();

    float dir = glm::dot(velocity,normal);
    if(dir>0.0f) rigidBodyA->AddVelocity(-dir*normal);

    DebugRenderer* debugrenderer = entityA->GetScene()->GetDebugRenderer();
    debugrenderer->DrawLine(transformA->position,transformA->position+normal*collision->penetration,glm::vec4(0.5f,0.5f,0.1f,1.0f));
    // if(relative_velocity_res>=0)  velocity_fixer = 0.0f;
    // else{
    //     velocity_fixer = -relative_velocity_res;
    // }
    // rigidBodyA->AddVelocity(velocity_fixer*normal);
    float correction_distance = collision->penetration + glm::dot(rigidBodyA->GetCorrection(),normal);
    if(correction_distance > 0.01f){
        glm::vec2 correction = -normal*((correction_distance-0.01f)*0.7f);
        transformA->position += correction;
        rigidBodyA->AddCorrection(correction);
    }
    // std::cout << "n=(" << normal.x << "," << normal.y << ") pen=" << collision->penetration
    //       << " depth=" << correction_distance << " vel=(" << velocity.x << "," << velocity.y << ")\n";
}