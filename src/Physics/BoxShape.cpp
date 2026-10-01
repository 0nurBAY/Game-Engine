//BoxShape.cpp

#include "Physics/BoxShape.h"
#include <cfloat>

BoxShape::BoxShape(float Width,float Height,glm::vec2 position,float rotation):
halfExtents(glm::vec2(Width*0.5,Height*0.5))
{
    type = ColliderType::Box;
    localTransform.position = position;
    localTransform.rotation = rotation;
}

void BoxShape::CalculateAABB(glm::vec2 e_position, float e_rotation){
    float max_x = -FLT_MAX;
    float min_x =  FLT_MAX;
    float max_y = -FLT_MAX;
    float min_y =  FLT_MAX;
    Transform2D worldTransform = GetWorldTransform(e_position, e_rotation);
    float rad = glm::radians(worldTransform.rotation);
    float cosr = glm::cos(rad);
    float sinr = glm::sin(rad);

    glm::vec2 corners[4] = {
        { -halfExtents.x, -halfExtents.y },
        {  halfExtents.x, -halfExtents.y },
        {  halfExtents.x,  halfExtents.y },
        { -halfExtents.x,  halfExtents.y }
    };

    for (auto& corner: corners){
        
        glm::vec2 rotated = 
        glm::vec2(corner.x * cosr - corner.y * sinr,
                  corner.x * sinr + corner.y * cosr);
        rotated += worldTransform.position;
        
        max_x = std::max(max_x,rotated.x);
        min_x = std::min(min_x,rotated.x);
        max_y = std::max(max_y,rotated.y);
        min_y = std::min(min_y,rotated.y);
    }

    aabb = {min_x,min_y,max_x,max_y};
}