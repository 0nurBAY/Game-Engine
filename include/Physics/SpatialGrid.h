//SpatialGrid.h

#pragma once

#include "Scene/Entity.h"
#include "Physics/ColliderShape.h"
#include "Physics/PhysicTypes.h"

#include <unordered_map>
#include <set>


class SpatialGrid{
private:
    constexpr static float CellSize = 200.0f;
public:
    static std::unordered_map<Grid,std::set<GridCell>,GridHash> GetGrid(std::vector<EntityCheck>& entities);
};
