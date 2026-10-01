//ColliderShape.cpp

#include "Physics/ColliderShape.h"

Transform2D ColliderShape::GetWorldTransform(glm::vec2 e_position, float e_rotation) const{
    float rad = glm::radians(e_rotation);
    float cosr = glm::cos(rad);
    float sinr = glm::sin(rad);

    glm::vec2 pos = glm::vec2(
        localTransform.position.x * cosr - localTransform.position.y * sinr,
        localTransform.position.y * cosr + localTransform.position.x * sinr
    );
    return {e_position+pos,e_rotation+localTransform.rotation};
}
AABB ColliderShape::GetAABB() const{
    return aabb;
}
ColliderType ColliderShape::GetShapeType() const{
    return type;
}