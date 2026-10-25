//PhysicSystem.h
#pragma once

#include "Scene/Scene.h"
#include "Event/Events.h"
#include "Physics/PhysicTypes.h"
#include "Physics/ColliderShape.h"
#include "Physics/SpatialGrid.h"
#include "Physics/CollisionDetector.h"
#include "Physics/CollisionSolver.h"

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <functional>

class PhysicSystem
{
private:
    std::vector<CandidatePair> candidates;
    std::unordered_map<ColliderType, std::unordered_map<ColliderType,std::function<ColliderResult(ColliderShape* shape1, ColliderShape* shape2,  glm::vec2 pos1, float rot1, glm::vec2 pos2, float rot2)>,ColliderHash>> colliders;
    std::unordered_map<Grid, std::vector<GridCell>, GridHash> grid;
    std::vector<Entity*> entities;
    std::vector<EntityCheck> Entities_in_Update_Box;
    std::vector<Entity*> Entities_out_Update_Box;
    std::vector<ColliderResult> collisionsres;
    Scene* currentScene   = nullptr;
    Camera* currentCamera = nullptr;
    float accumulator = 0;
    float fixed = 0;
    void Step();
public:
    void Init(float fixed, Scene* scene);
    void FixedUpdate(float dt);
    void AABBCompare();
    void NarrowPhase();
    void CollisionResult();
    void FindPhysicEntities();
    void EntityAABB_finder();
    void UpdatePhysicEntities();
    std::vector<ColliderResult> GetCollisions() const;
    void OnEvent(Event& event);
    
};
