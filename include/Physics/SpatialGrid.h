//SpatialGrid.h

#pragma once

#include "Scene/Entity.h"
#include "Physics/ColliderShape.h"
#include "Physics/PhysicTypes.h"

#include <unordered_map>
#include <set>


class SpatialGrid{
public:
    constexpr static float CellSize = 200.0f;
    static void GetGrid(std::vector<EntityCheck>& entities,std::unordered_map<Grid, std::vector<GridCell>,GridHash>& grid);
};
