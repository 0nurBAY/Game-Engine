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

    currentScene = scene;
    currentCamera = scene->GetEntityCamera();
    FindPhysicEntities();
    EntityAABB_finder();
    // std::cout << "Test1\n";
}

void PhysicSystem::FixedUpdate(float dt){
    accumulator+=dt;
    int counter = 0;
    while(accumulator>=fixed && counter<5){
        Step();
        accumulator-=fixed;
        counter++;
    }
    if(accumulator >= fixed)
    accumulator = std::fmod(accumulator, fixed);
    // std::cout << "Test2\n";
}

void PhysicSystem::Step(){
    collisionsres.clear();
    candidates.clear();
    if(entities.empty()) return;
    EntityAABB_finder();
    AABBCompare();
    NarrowPhase();
    CollisionResult();
    UpdatePhysicEntities();
    
}

void PhysicSystem::FindPhysicEntities(){
    for(auto& entity:currentScene->GetEntityManager().GetEntites()){
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
    Entities_in_Update_Box.clear();
    Entities_out_Update_Box.clear();
    
    float cam_widht = currentCamera->GetWidth()*0.5f  *currentCamera->GetZoom() + 500.0f;
    float cam_height = currentCamera->GetHeight()*0.5f*currentCamera->GetZoom() + 500.0f;
    float cam_x = currentCamera->GetPosition().x;
    float cam_y = currentCamera->GetPosition().y;
    for(auto entity: entities){
        TransformComp* transform = entity->GetComponent<TransformComp>();
        glm::vec2 entity_posX = transform->GetMinMaxX();
        glm::vec2 entity_posY = transform->GetMinMaxY();
        if(entity_posX.x - cam_x > cam_widht ||
           entity_posX.y - cam_x <-cam_widht ||
           entity_posY.y - cam_y <-cam_height||
           entity_posY.x - cam_y > cam_height
        ) {Entities_out_Update_Box.push_back(entity); continue;}

        std::vector<std::pair<AABB, ColliderShape*>> second;
        for(auto& collider:entity->GetComponent<ColliderComponent>()->Getcolliders()){
            collider->CalculateAABB(
            transform->position,
            transform->rotation
            );
            second.push_back({collider->GetAABB(), collider});
        }
        Entities_in_Update_Box.push_back({entity,second});
        


    }
}
void PhysicSystem::AABBCompare()
{
    for(auto&[k,v]: grid) v.clear();
    SpatialGrid::GetGrid(Entities_in_Update_Box,grid);
    if(grid.empty()) {return;}

    for(auto& [cell, entitiesInCell]:grid){

    for(auto it1 = entitiesInCell.begin(); it1 != entitiesInCell.end(); ++it1)
    {
        
        auto* entity1 = it1->entity;
        auto aabb1 = it1->collider->GetAABB();
        bool sleeping =(it1->rigidbody)? (it1->rigidbody->IsSleeping()):true;
        bool static1 = !it1->rigidbody || it1->rigidbody->IsStatic();
        for(auto it2 = std::next(it1); it2 != entitiesInCell.end(); ++it2)
        {

            auto* entity2 = it2->entity;       
            if(entity1 == entity2) continue;
            bool static2 = !it2->rigidbody || it2->rigidbody->IsStatic();
            if(static1 && static2)continue;
            bool sleeping2 = (it2->rigidbody)? (it2->rigidbody->IsSleeping()):true;
            if(sleeping && sleeping2) continue;
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
            Grid left_bottom_corner = {static_cast<int>(std::floor(std::max(aabb1.minx,aabb2.minx)/SpatialGrid::CellSize)),static_cast<int>(std::floor(std::max(aabb1.miny,aabb2.miny)/SpatialGrid::CellSize))};
            if(!(cell == left_bottom_corner)) continue;
                // std::cout << "Collision Between Entity " << entity1->GetID() << " and Entity " << entity2->GetID() << "\n\n";

                candidates.push_back({entity1,it1->collider, entity2, it2->collider});
            }
            // else{
            //     entity1->GetComponent<ColliderComponent>()->ColliderColorDefault();
            //     entity2->GetComponent<ColliderComponent>()->ColliderColorDefault();
            // }
        }
    }
    }
}


void PhysicSystem::OnEvent(Event &event){
    EventDispatcher dispatcher(event);

    dispatcher.Dispatcher<PhysicsEntityAddEvent>(
        [this](PhysicsEntityAddEvent& event){
            auto* entity = event.GetEntity();
            if(entity->GetType() & static_cast<std::uint32_t>(CopmonentCategory::Physic)){
                for(auto& collider:entity->GetComponent<ColliderComponent>()->Getcolliders()){
                    collider->CalculateAABB(
                    entity->GetComponent<TransformComp>()->position,
                    entity->GetComponent<TransformComp>()->rotation
                    );
                }
                this->entities.push_back(entity);
            }
        }
    );
    
    dispatcher.Dispatcher<PhysicsEntityRemoveEvent>(
        [this](PhysicsEntityRemoveEvent& event){
            //Bunu şimdilik boş ver
        }
    );
}

void PhysicSystem::NarrowPhase(){
    for(auto& candidatepair: candidates){
        Entity* entity1 = candidatepair.entity1;
        Entity* entity2 = candidatepair.entity2;
        auto* collider1 = candidatepair.collider1;
        auto* collider2 = candidatepair.collider2;

        TransformComp* transfrom1 = entity1->GetComponent<TransformComp>();
        TransformComp* transfrom2 = entity2->GetComponent<TransformComp>();
        glm::vec2 pos1 = transfrom1->position;
        glm::vec2 pos2 = transfrom2->position;
        float rot1 = transfrom1->rotation;
        float rot2 = transfrom2->rotation;

        auto collision = colliders[collider1->GetShapeType()][collider2->GetShapeType()](collider1,collider2,pos1,rot1,pos2,rot2);
        if(collision.collision){
            // entity1->GetComponent<ColliderComponent>()->SetColliderColor(glm::vec4(0.8f,0.4f,0.15f,1.0f));
            // entity2->GetComponent<ColliderComponent>()->SetColliderColor(glm::vec4(0.8f,0.4f,0.15f,1.0f));
            // std::cout <<"Collision detected between: "<< entity1->GetName() << entity2->GetName() <<"\n";
            // std::cout <<"Direction: " << collision.normal.x <<","<<collision.normal.y << "\nPenetration: "<< collision.penetration <<"\n"; 
            
            collision.entityA = entity1;
            collision.entityB = entity2;
            collision.typeA = (entity1->HasComponent<RigidBodyComponent>())? entity1->GetComponent<RigidBodyComponent>()->GetBodyType(): BodyType::Static;
            collision.typeB = (entity2->HasComponent<RigidBodyComponent>())? entity2->GetComponent<RigidBodyComponent>()->GetBodyType(): BodyType::Static;

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
        CollisionSolver::Solve(&collision);
    }
}

void PhysicSystem::UpdatePhysicEntities(){
    for(auto& [entity,sec]: Entities_in_Update_Box){
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
