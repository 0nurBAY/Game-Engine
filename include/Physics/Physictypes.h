//PhysicTypes.h
#pragma once

#include <cstdint>
#include <cstddef>
#include <functional>
#include <utility>
#include <vector>
#include <set>
#include <unordered_set>
#include <array>
#include <glm/vec2.hpp>

class Entity;
class RigidBodyComponent;
class ColliderShape;
struct ColliderResult;

enum class ColliderType{
    Box,
    Circle
};


enum class BodyType{
    Dynamic,
    Static,
    Kinematic
};

struct ColliderHash{
    std::size_t operator()(const ColliderType& type) const;
};

struct BodyTypeHash{
    std::size_t operator()(const BodyType& type) const;
};


struct Transform2D{
    glm::vec2 position;
    float rotation;
};


struct AABB{
    float minx;
    float miny;
    float maxx;
    float maxy;
};


struct CandidatePair{
    Entity* entity1;
    ColliderShape* collider1;

    Entity* entity2;
    ColliderShape* collider2;

    bool operator<(const CandidatePair& other) const;
    bool operator==(const CandidatePair& other) const;
};


struct CandidatePairHash{
    std::size_t operator()(const CandidatePair& pair) const;
};


struct EntityCheck{
    Entity* entity;
    std::vector<std::pair<AABB, ColliderShape*>> aabb;
};


struct GridCell{
    Entity* entity;
    ColliderShape* collider;
    RigidBodyComponent* rigidbody;
    bool operator<(const GridCell& other) const;
};


struct Grid{
    int x;
    int y;

    bool operator==(const Grid& other) const;
};


struct GridHash{
    std::size_t operator()(const Grid& grid) const;
};

struct ColliderResult{
    bool collision;
    glm::vec2 normal;
    float penetration;
    std::vector<glm::vec2> contacts;
    Entity* entityA;
    Entity* entityB;
    BodyType typeA;
    BodyType typeB;
    // glm::vec2 center1;
    // glm::vec2 center2;
    
    // glm::vec2 ACoord1;
    // glm::vec2 ACoord2;
    
    // glm::vec2 BCoord1;
    // glm::vec2 BCoord2;

    // float radius1;
    // float radius2;
    // glm::vec2 halfextend2;
    // glm::vec2 halfextend2;
    // float rot1;
    // float rot2;
    // std::array<glm::vec2, 2> contactPoints;
    // int contactCount = 0;

};
