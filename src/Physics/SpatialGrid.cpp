//SpatialGrid.cpp

#include "Physics/SpatialGrid.h"

void SpatialGrid::GetGrid(std::vector<EntityCheck>& entities,std::unordered_map<Grid, std::vector<GridCell>,GridHash> &grid){

    // std::cout << "----------------\nEntityCheck count: " << entities.size() << "----------------\n";
    for(size_t i = 0; i < entities.size(); ++i){
        auto& check = entities[i];
        RigidBodyComponent* rigidbody = check.entity->GetComponent<RigidBodyComponent>();
        // std::cout << "Index: " << i
        //       << " Entity ID: " << check.entity->GetID()
        //       << "\n";

        // std::cout << "Processing Entity ID: " << check.entity->GetID() << "\n";
        for(auto& [aabb, collider]:check.aabb){
            int minCellx = static_cast<int>(std::floor(aabb.minx/CellSize));
            int maxCellx = static_cast<int>(std::floor(aabb.maxx/CellSize));
            int minCelly = static_cast<int>(std::floor(aabb.miny/CellSize));
            int maxCelly = static_cast<int>(std::floor(aabb.maxy/CellSize));
            // std::cout << "AABB: [" << aabb.minx << ", " << aabb.miny << ", " << aabb.maxx << ", " << aabb.maxy << "]\n";    
            // std::cout << "Grid Cells: x(" << minCellx << " to " << maxCellx << "), y(" << minCelly << " to " << maxCelly << ")\n";
            for(int x = minCellx; x <= maxCellx; x++){
                for(int y = minCelly; y <= maxCelly; y++){
                    grid[{x, y}].push_back({check.entity, collider,rigidbody});
                }
            }
        }
    }
    
}