//PhysicSystem.cpp
#include "Physics/PhysicSystem.h"
#include <iostream>

void PhysicSystem::Init(float fixed){
    this->fixed = fixed;
    collisions[ColliderType::Circle][ColliderType::Circle] = ([this](ColliderShape* shape1, ColliderShape* shape2,  glm::vec2 pos1, float rot1, glm::vec2 pos2, float rot2){return CollisionDetector::CircleVsCircle(shape1, shape2, pos1, rot1, pos2, rot2);});
    collisions[ColliderType::Box]   [ColliderType::Box]    = ([this](ColliderShape* shape1, ColliderShape* shape2,  glm::vec2 pos1, float rot1, glm::vec2 pos2, float rot2){return CollisionDetector::BoxVsBox(shape1, shape2, pos1, rot1, pos2, rot2);});
    collisions[ColliderType::Circle][ColliderType::Box]    = ([this](ColliderShape* shape1, ColliderShape* shape2,  glm::vec2 pos1, float rot1, glm::vec2 pos2, float rot2){return CollisionDetector::CircleVsBox(shape1, shape2, pos1, rot1, pos2, rot2);}); //Box first, Circle second
    collisions[ColliderType::Box]   [ColliderType::Circle] = ([this](ColliderShape* shape1, ColliderShape* shape2,  glm::vec2 pos1, float rot1, glm::vec2 pos2, float rot2){return CollisionDetector::CircleVsBox(shape2, shape1, pos2, rot2, pos1, rot1);}); //Circle first, Box second
}

void PhysicSystem::FixedUpdate(float dt, Scene *scene){
    accumulator+=dt;
    entities.clear();
    collisionsres.clear();
    FindPhysicEntities(scene);
    while(accumulator>=fixed){
        Step();
        accumulator-=fixed;
    }

}

void PhysicSystem::Step(){
    candidates.clear();
    if(entities.empty()) return;
    UpdatePhysicEntities();
    AABBCompare();
    NarrowPhase();
    CollisionResault();
    
}

void PhysicSystem::FindPhysicEntities(Scene *scene){
    for(auto& entity:scene->GetEntityManager().GetEntites()){
        if(entity.second.get()->GetType() & static_cast<std::uint32_t>(CopmonentCategory::Physic)){
            std::vector<std::pair<AABB, ColliderShape*>> second;
            for(auto& collider:entity.second.get()->GetComponent<ColliderComponent>()->Getcolliders()){
                collider->CalculateAABB(
                entity.second.get()->GetComponent<TransformComp>()->position,
                entity.second.get()->GetComponent<TransformComp>()->rotation
                );
                second.push_back({collider->GetAABB(), collider});
            }
            entities.push_back({entity.second.get(), second});
        }
    }
    // for(auto& entity:entities){
        // std::cout << "Entity ID: " << entity.entity->GetID() << ", AABB Count: " << entity.aabb.size() << "\n";
        // for(auto& [aabb, collider]:entity.aabb){
        //     std::cout << "AABB: [" << aabb.minx << ", " << aabb.miny << ", " << aabb.maxx << ", " << aabb.maxy << "]\n";
        // }
    // }
}
void PhysicSystem::AABBCompare()
{
    auto grid = SpatialGrid::GetGrid(entities);
    if(grid.empty()) {return;}

    for(auto& [cell, entitiesInCell]:grid){
    for(auto it1 = entitiesInCell.begin(); it1 != entitiesInCell.end(); ++it1)
    {
        auto* entity1 = it1->entity;
        auto aabb1 = it1->collider->GetAABB();
        for(auto it2 = std::next(it1); it2 != entitiesInCell.end(); ++it2)
        {
            auto* entity2 = it2->entity;
            auto aabb2 = it2->collider->GetAABB();
            // std::cout << "Grid:\t" << cell.x << ", " << cell.y << "\n";
            // std::cout << "Entity1 ID: " << entity1->GetID() << ", AABB: [" << aabb1.minx << ", " << aabb1.miny << ", " << aabb1.maxx << ", " << aabb1.maxy << "]\n";
            // std::cout << "Entity2 ID: " << entity2->GetID() << ", AABB: [" << aabb2.minx << ", " << aabb2.miny << ", " << aabb2.maxx << ", " << aabb2.maxy << "]\n";
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
        }
    }
    }
}


// void PhysicSystem::OnEvent(Event &event){
//     EventDispatcher dispatcher(event);

//     dispatcher.Dispatcher<PhysicsEntityAddEvent>(
//         [this](){}
//     );
// }

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
        auto& collision = collisions[collider1->GetShapeType()][collider2->GetShapeType()](collider1,collider2,pos1,rot1,pos2,rot2);
        if(collision.collision){
            // entity1->OnEvent(CollisionEvent(entity2));
            // entity2->OnEvent(CollisionEvent(entity1));
            // std::cout <<"Collision detected between: "<< entity1->GetName() << entity2->GetName() <<"\n";
            // std::cout <<"Direction: " << collision.normal.x <<","<<collision.normal.y << "\nPenetration: "<< collision.penetration <<"\n"; 
            collision.entityA = entity1;
            collision.entityB = entity2;
            collisionsres.push_back(collision);
        }
    }

}

void PhysicSystem::CollisionResault(){
    
}

void PhysicSystem::UpdatePhysicEntities(){
    for(auto& [entity,sec]: entities){
        if(!entity->HasComponent<RigidBodyComponent>()) continue;
        auto* rigidbody = entity->GetComponent<RigidBodyComponent>();
        rigidbody->UpdateRigidBody(fixed);
        auto* transform = entity->GetComponent<TransformComp>();
        transform->position += rigidbody->GetVelocity() * fixed;
    }
}
std::vector<ColliderResult> PhysicSystem::GetCollisions()const {
    return collisionsres;
}
