//CollisionSolver.cpp

#include "Physics/CollisionSolver.h"
#include "Scene/Entity.h"
void CollisionSolver::StaticVsDynamic(ColliderResult *collision){
    Entity* entityA = collision->entityA;
    Entity* entityB = collision->entityB;

    auto* transformA = entityA->GetComponent<TransformComp>();
    auto* transformB = entityB->GetComponent<TransformComp>();
    auto* rigidBodyA = entityA->GetComponent<RigidBodyComponent>();
    auto* rigidBodyB = entityB->GetComponent<RigidBodyComponent>();

    
}