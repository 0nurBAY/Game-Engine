//CircleShape.cpp

#include "Physics/CircleShape.h"

CircleShape::CircleShape(float radius, glm::vec2 position) : radius(radius) {
    type = ColliderType::Circle;
    localTransform.position = position;
}

void CircleShape::CalculateAABB(glm::vec2 e_position, float e_rotation) {
    float worldX = e_position.x + localTransform.position.x;
    float worldY = e_position.y + localTransform.position.y;
    aabb = {worldX - radius, worldY - radius, worldX + radius, worldY + radius};
}

float CircleShape::GetRadius() const{
    return radius;
}