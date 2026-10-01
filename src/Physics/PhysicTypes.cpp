//PhysicTypes.cpp

#include "Physics/PhysicTypes.h"

#include "Scene/Entity.h"
#include "Physics/ColliderShape.h"

#include <functional>
#include <cstdint>


std::size_t ColliderHash::operator()(const ColliderType& type) const
{
    return std::hash<uint32_t>()(
        static_cast<uint32_t>(type)
    );
}


bool CandidatePair::operator<(const CandidatePair& other) const
{
    uint64_t thisEntityLow;
    uint64_t thisEntityHigh;

    uint64_t otherEntityLow;
    uint64_t otherEntityHigh;


    if(entity1->GetID() < entity2->GetID())
    {
        thisEntityLow = entity1->GetID();
        thisEntityHigh = entity2->GetID();
    }
    else
    {
        thisEntityLow = entity2->GetID();
        thisEntityHigh = entity1->GetID();
    }


    if(other.entity1->GetID() < other.entity2->GetID())
    {
        otherEntityLow = other.entity1->GetID();
        otherEntityHigh = other.entity2->GetID();
    }
    else
    {
        otherEntityLow = other.entity2->GetID();
        otherEntityHigh = other.entity1->GetID();
    }


    if(thisEntityLow != otherEntityLow)
        return thisEntityLow < otherEntityLow;

    if(thisEntityHigh != otherEntityHigh)
        return thisEntityHigh < otherEntityHigh;


    std::less<ColliderShape*> colliderLess;

    ColliderShape* thisColliderLow;
    ColliderShape* thisColliderHigh;

    ColliderShape* otherColliderLow;
    ColliderShape* otherColliderHigh;


    if(entity1->GetID() < entity2->GetID())
    {
        thisColliderLow = collider1;
        thisColliderHigh = collider2;
    }
    else
    {
        thisColliderLow = collider2;
        thisColliderHigh = collider1;
    }


    if(other.entity1->GetID() < other.entity2->GetID())
    {
        otherColliderLow = other.collider1;
        otherColliderHigh = other.collider2;
    }
    else
    {
        otherColliderLow = other.collider2;
        otherColliderHigh = other.collider1;
    }


    if(thisColliderLow != otherColliderLow)
        return colliderLess(thisColliderLow, otherColliderLow);

    return colliderLess(thisColliderHigh, otherColliderHigh);
}


bool CandidatePair::operator==(const CandidatePair& other) const
{
    bool sameOrder =
        entity1 == other.entity1 &&
        collider1 == other.collider1 &&
        entity2 == other.entity2 &&
        collider2 == other.collider2;


    bool reverseOrder =
        entity1 == other.entity2 &&
        collider1 == other.collider2 &&
        entity2 == other.entity1 &&
        collider2 == other.collider1;


    return sameOrder || reverseOrder;
}


std::size_t CandidatePairHash::operator()(const CandidatePair& pair) const
{
    std::hash<uint64_t> entityHash;
    std::hash<ColliderShape*> colliderHash;


    uint64_t entityLow;
    uint64_t entityHigh;

    ColliderShape* colliderLow;
    ColliderShape* colliderHigh;


    if(pair.entity1->GetID() < pair.entity2->GetID())
    {
        entityLow = pair.entity1->GetID();
        entityHigh = pair.entity2->GetID();

        colliderLow = pair.collider1;
        colliderHigh = pair.collider2;
    }
    else
    {
        entityLow = pair.entity2->GetID();
        entityHigh = pair.entity1->GetID();

        colliderLow = pair.collider2;
        colliderHigh = pair.collider1;
    }


    std::size_t h1 = entityHash(entityLow);
    std::size_t h2 = entityHash(entityHigh);

    std::size_t h3 = colliderHash(colliderLow);
    std::size_t h4 = colliderHash(colliderHigh);


    std::size_t result = h1;

    result ^= h2 + 0x9e3779b9 + (result << 6) + (result >> 2);
    result ^= h3 + 0x9e3779b9 + (result << 6) + (result >> 2);
    result ^= h4 + 0x9e3779b9 + (result << 6) + (result >> 2);


    return result;
}


bool GridCell::operator<(const GridCell& other) const
{
    if(entity->GetID() != other.entity->GetID())
        return entity->GetID() < other.entity->GetID();

    return std::less<ColliderShape*>{}(collider, other.collider);
}


bool Grid::operator==(const Grid& other) const
{
    return x == other.x &&
           y == other.y;
}


std::size_t GridHash::operator()(const Grid& grid) const
{
    std::size_t h1 = std::hash<int>()(grid.x);
    std::size_t h2 = std::hash<int>()(grid.y);

    return h1 ^ (h2 << 2);
}