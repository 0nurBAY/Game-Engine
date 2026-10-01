//ColliderShape.h
#pragma once

#include "Physics/PhysicTypes.h"
#include <glm/glm.hpp>

class ColliderShape
{
public:
    glm::vec2 GetLocalPos() const;
    float     GetLocalRotation() const;
    ColliderType GetShapeType() const;
    Transform2D GetWorldTransform(glm::vec2 e_position,float e_rotation) const;
    virtual void CalculateAABB(glm::vec2 e_position, float e_rotation){};
    AABB GetAABB() const;
protected:
    Transform2D localTransform;
    ColliderType type;
    AABB aabb = {1.0f,0.0f,0.0f,0.0f};
};
