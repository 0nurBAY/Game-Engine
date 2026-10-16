//CollisionSolver.cpp

#include "Physics/CollisionSolver.h"
#include "Renderer/DebugRenderer.h"
#include "Scene/Scene.h"
#include "Scene/Entity.h"
void CollisionSolver::Solve(ColliderResult *collision,bool reverse){
    Entity* entityA  = collision->entityA; 
    Entity* entityB  = collision->entityB; 
    glm::vec2 normal = collision->normal; 
    auto* transformA = entityA->GetComponent<TransformComp>();
    auto* transformB = entityB->GetComponent<TransformComp>();
    auto* rigidBodyA = entityA->GetComponent<RigidBodyComponent>();
    auto* rigidBodyB = entityB->GetComponent<RigidBodyComponent>();
    float r_massA = rigidBodyA->GetInvMass();
    float r_massB = rigidBodyB->GetInvMass();
    glm::vec2 velocityA = rigidBodyA->GetVelocity();
    glm::vec2 velocityB = rigidBodyB->GetVelocity();

    // float dir = glm::dot(velocityA,normal);
    // if(dir>0.0f) rigidBodyA->AddVelocity(-dir*normal);
    
    DebugRenderer* debugrenderer = entityA->GetScene()->GetDebugRenderer();
    debugrenderer->DrawLine(transformA->position,transformA->position+normal*collision->penetration,glm::vec4(0.5f,0.5f,0.1f,1.0f));
    
    
    float relatives_dot = glm::dot((velocityB-velocityA),normal);
    float R_mass_sum = (r_massA+r_massB);
    if(R_mass_sum == 0) return;
    if(relatives_dot<=0){
        float impuls = -(1+std::max(rigidBodyA->GetRestitution(),rigidBodyB->GetRestitution())) * relatives_dot / R_mass_sum;
        rigidBodyA->AddVelocity(-impuls*r_massA*normal);
        rigidBodyB->AddVelocity(impuls*r_massB*normal);
        // std::cout << "vn=(" << relatives_dot << ") Rmass A:" << r_massA << " Rmass B:" << r_massB << "Restituion: " <<std::max(rigidBodyA->GetRestitution(),rigidBodyB->GetRestitution())<<"\n";
    }
    
    float correction_distance = (collision->penetration + glm::dot(rigidBodyA->GetCorrection(),normal) - glm::dot(rigidBodyB->GetCorrection(),normal));
    if(correction_distance > 0.01f){
        glm::vec2 correction = normal*((correction_distance-0.01f)*0.7f);
        transformA->position -= correction * r_massA / R_mass_sum;
        rigidBodyA->AddCorrection(-correction * r_massA / R_mass_sum);
        transformB->position += correction * r_massB / R_mass_sum;
        rigidBodyB->AddCorrection(correction * r_massB / R_mass_sum);
    }
    
    // std::cout << "n=(" << normal.x << "," << normal.y << ") pen=" << collision->penetration
    //       << " depth=" << correction_distance << " velA=(" << velocityA.x << "," << velocityA.y<< ") velB=(" << velocityB.x << "," << velocityB.y << ")\n";

}