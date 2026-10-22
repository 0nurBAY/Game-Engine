//PhysicSystem.cpp
#include "Physics/PhysicSystem.h"
#include "Event/PhysicEvents.h"
#include <iostream>

void PhysicSystem::Init(float fixed, Scene *scene){
    this->fixed = fixed;
    colliders[ColliderType::Circle][ColliderType::Circle] = ([this](ColliderShape* shape1, ColliderShape* shape2,  glm::vec2 pos1, float rot1, glm::vec2 pos2, float rot2){return CollisionDetector::CircleVsCircle(shape1, shape2, pos1, rot1, pos2, rot2);});
    colliders[ColliderType::Box]   [ColliderType::Box]    = ([this](ColliderShape* shape1, ColliderShape* shape2,  glm::vec2 pos1, float rot1, glm::vec2 pos2, float rot2){return CollisionDetector::BoxVsBox(shape1, shape2, pos1, rot1, pos2, rot2);});
    colliders[ColliderType::Circle][ColliderType::Box]    = ([this](ColliderShape* shape1, ColliderShape* shape2,  glm::vec2 pos1, float rot1, glm::vec2 pos2, float rot2){return CollisionDetector::CircleVsBox(shape1, shape2, pos1, rot1, pos2, rot2);}); //Circle first, Box second
    colliders[ColliderType::Box]   [ColliderType::Circle] = ([this](ColliderShape* shape1, ColliderShape* shape2,  glm::vec2 pos1, float rot1, glm::vec2 pos2, float rot2){
        ColliderResult res = CollisionDetector::CircleVsBox(shape2, shape1, pos2, rot2, pos1, rot1);
        res.normal = -res.normal;
        return res;}); //Circle first, Box second

    collisions[BodyType::Static][BodyType::Dynamic]       = ([this](ColliderResult* collision){CollisionSolver::Solve(collision,1);});
    collisions[BodyType::Dynamic][BodyType::Static]       = ([this](ColliderResult* collision){CollisionSolver::Solve(collision,0);});
    collisions[BodyType::Dynamic][BodyType::Dynamic]      = ([this](ColliderResult* collision){CollisionSolver::Solve(collision,0);});
    FindPhysicEntities(scene);
    EntityAABB_finder();
    // std::cout << "Test1\n";
}

void PhysicSystem::FixedUpdate(float dt){
    accumulator+=dt;
    collisionsres.clear();
    while(accumulator>=fixed){
        Step();
        accumulator-=fixed;
    }
    // std::cout << "Test2\n";
}

void PhysicSystem::Step(){
    candidates.clear();
    if(entities.empty()) return;
    UpdatePhysicEntities();
    EntityAABB_finder();
    AABBCompare();
    NarrowPhase();
    CollisionResult();
    
}

void PhysicSystem::FindPhysicEntities(Scene *scene){
    for(auto& entity:scene->GetEntityManager().GetEntites()){
        if(entity.second.get()->GetType() & static_cast<std::uint32_t>(CopmonentCategory::Physic)){
            entities.push_back(entity.second.get());
        }
    }
    // for(auto& entity:entities){
        // std::cout << "Entity ID: " << entity.entity->GetID() << ", AABB Count: " << entity.aabb.size() << "\n";
        // for(auto& [aabb, collider]:entity.aabb){
        //     std::cout << "AABB: [" << aabb.minx << ", " << aabb.miny << ", " << aabb.maxx << ", " << aabb.maxy << "]\n";
        // }
    // }
}
void PhysicSystem::EntityAABB_finder(){
    entities_with_AABBs.clear();
    for(auto entity: entities){
        std::vector<std::pair<AABB, ColliderShape*>> second;
        for(auto& collider:entity->GetComponent<ColliderComponent>()->Getcolliders()){
            collider->CalculateAABB(
            entity->GetComponent<TransformComp>()->position,
            entity->GetComponent<TransformComp>()->rotation
            );
            second.push_back({collider->GetAABB(), collider});
        }
        entities_with_AABBs.push_back({entity,second});

    }
}
void PhysicSystem::AABBCompare()
{
    auto grid = SpatialGrid::GetGrid(entities_with_AABBs);
    if(grid.empty()) {return;}

    for(auto& [cell, entitiesInCell]:grid){

    for(auto it1 = entitiesInCell.begin(); it1 != entitiesInCell.end(); ++it1)
    {

        auto* entity1 = it1->entity;
        auto aabb1 = it1->collider->GetAABB();
        RigidBodyComponent* rigidbody1 = entity1->GetComponent<RigidBodyComponent>();
        bool sleeping = !(rigidbody1->IsMoving());
        for(auto it2 = std::next(it1); it2 != entitiesInCell.end(); ++it2)
        {
            auto* entity2 = it2->entity;            
            RigidBodyComponent* rigidbody2 = entity2->GetComponent<RigidBodyComponent>();
            if(sleeping && (!(rigidbody2->IsMoving()) && (rigidbody2->GetBodyType()!=BodyType::Static)) ) continue;
            auto aabb2 = it2->collider->GetAABB();
            // std::cout << "Grid:\t" << cell.x << ", " << cell.y << "\n";
            // std::cout << "Entity1 ID: " << entity1->GetID() << ", AABB: [" << aabb1.minx << ", " << aabb1.miny << ", " << aabb1.maxx << ", " << aabb1.maxy << "]\n";
            // std::cout << "Entity2 ID: " << entity2->GetID() << ", AABB: [" << aabb2.minx << ", " << aabb2.miny << ", " << aabb2.maxx << ", " << aabb2.maxy << "]\n";
            if((rigidbody1->GetBodyType()==BodyType::Static)&&(rigidbody2->GetBodyType()==BodyType::Static))continue;
            bool collision =
                !(aabb1.maxx < aabb2.minx ||
                  aabb2.maxx < aabb1.minx ||
                  aabb1.maxy < aabb2.miny ||
                  aabb2.maxy < aabb1.miny);
            if(collision)
            {
                // std::cout << "Collision Between Entity " << entity1->GetID() << " and Entity " << entity2->GetID() << "\n\n";
                candidates.insert({entity1,it1->collider, entity2, it2->collider});
            }
            else{
                entity1->GetComponent<ColliderComponent>()->ColliderColorDefault();
                entity2->GetComponent<ColliderComponent>()->ColliderColorDefault();
            }
        }
    }
    }
}


void PhysicSystem::OnEvent(Event &event){
    EventDispatcher dispatcher(event);

    dispatcher.Dispatcher<PhysicsEntityAddEvent>(
        [this](PhysicsEntityAddEvent event){
            auto* entity = event.GetEntity();
            if(entity->GetType() & static_cast<std::uint32_t>(CopmonentCategory::Physic)){
                std::vector<std::pair<AABB, ColliderShape*>> second;
                for(auto& collider:entity->GetComponent<ColliderComponent>()->Getcolliders()){
                    collider->CalculateAABB(
                    entity->GetComponent<TransformComp>()->position,
                    entity->GetComponent<TransformComp>()->rotation
                    );
                    second.push_back({collider->GetAABB(), collider});
                }
                this->entities.push_back(entity);
            }
        }
    );
    
    dispatcher.Dispatcher<PhysicsEntityRemoveEvent>(
        [this](PhysicsEntityRemoveEvent){
        }
    );
}

void PhysicSystem::NarrowPhase(){
    for(auto& candidatepair: candidates){
        Entity* entity1 = candidatepair.entity1;
        Entity* entity2 = candidatepair.entity2;
        auto* collider1 = candidatepair.collider1;
        auto* collider2 = candidatepair.collider2;

        glm::vec2 pos1 = entity1->GetComponent<TransformComp>()->position;
        glm::vec2 pos2 = entity2->GetComponent<TransformComp>()->position;
        float rot1 = entity1->GetComponent<TransformComp>()->rotation;
        float rot2 = entity2->GetComponent<TransformComp>()->rotation;
        auto& collision = colliders[collider1->GetShapeType()][collider2->GetShapeType()](collider1,collider2,pos1,rot1,pos2,rot2);
        if(collision.collision){
            // entity1->GetComponent<ColliderComponent>()->SetColliderColor(glm::vec4(0.8f,0.4f,0.15f,1.0f));
            // entity2->GetComponent<ColliderComponent>()->SetColliderColor(glm::vec4(0.8f,0.4f,0.15f,1.0f));
            // std::cout <<"Collision detected between: "<< entity1->GetName() << entity2->GetName() <<"\n";
            // std::cout <<"Direction: " << collision.normal.x <<","<<collision.normal.y << "\nPenetration: "<< collision.penetration <<"\n"; 
            
            collision.entityA = entity1;
            collision.entityB = entity2;
            auto* rigidbodyA = entity1->GetComponent<RigidBodyComponent>();
            auto* rigidbodyB = entity2->GetComponent<RigidBodyComponent>();
            collision.typeA = rigidbodyA->GetBodyType();
            collision.typeB = rigidbodyB->GetBodyType();

            collisionsres.push_back(collision);
        }
        // else{
        //     entity1->GetComponent<ColliderComponent>()->ColliderColorDefault();
        //     entity2->GetComponent<ColliderComponent>()->ColliderColorDefault();
        // }
    }
}

void PhysicSystem::CollisionResult(){
    for(auto& collision: collisionsres){
        collisions[collision.typeA][collision.typeB](&collision);
    }
}

void PhysicSystem::UpdatePhysicEntities(){
    for(auto& [entity,sec]: entities_with_AABBs){
        if(!entity->HasComponent<RigidBodyComponent>()) continue;
        auto* rigidbody = entity->GetComponent<RigidBodyComponent>();
        rigidbody->UpdateRigidBody(fixed);
        auto* transform = entity->GetComponent<TransformComp>();
        transform->position += rigidbody->GetVelocity() * fixed;
        rigidbody->ResetCorrection();
    }
}
std::vector<ColliderResult> PhysicSystem::GetCollisions() const {
    return collisionsres;
}
