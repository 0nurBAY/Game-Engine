//PhysicTypes.h
#pragma once

#include <cstdint>
#include <cstddef>
#include <functional>
#include <utility>
#include <vector>
#include <set>
#include <unordered_set>

#include <glm/vec2.hpp>

class Entity;
class ColliderShape;


enum class ColliderType{
    Box,
    Circle
};


struct ColliderHash{
    std::size_t operator()(const ColliderType& type) const;
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
    glm::vec2 contact1;
    glm::vec2 contact2;
    float penetration;
    glm::vec2 center1;
    glm::vec2 center2;
    float radius1;
    float radius2;

};