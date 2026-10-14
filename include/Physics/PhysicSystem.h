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
    std::unordered_set<CandidatePair, CandidatePairHash> candidates;
    std::unordered_map<ColliderType, std::unordered_map<ColliderType,std::function<ColliderResult(ColliderShape* shape1, ColliderShape* shape2,  glm::vec2 pos1, float rot1, glm::vec2 pos2, float rot2)>,ColliderHash>> colliders;
    std::unordered_map<BodyType, std::unordered_map<BodyType,std::function<void(ColliderResult* collision)>,BodyTypeHash>> collisions;
    std::vector<EntityCheck> entities;
    std::vector<ColliderResult> collisionsres;
    float accumulator = 0;
    float fixed = 0;
    void Step();
public:
    void Init(float fixed);
    void FixedUpdate(float dt, Scene* scene);
    void AABBCompare();
    void NarrowPhase();
    void CollisionResult();
    void FindPhysicEntities(Scene* scene);
    void UpdatePhysicEntities();
    std::vector<ColliderResult> GetCollisions() const;
    void OnEvent(Event& event);
    
};
