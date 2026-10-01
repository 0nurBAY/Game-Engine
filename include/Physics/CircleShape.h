//CircleShape.h

#pragma once

#include "Physics/ColliderShape.h"
#include <glm/glm.hpp>

class CircleShape: public ColliderShape
{
private:
    float radius;
public:
    CircleShape(float radius, glm::vec2 position);
    float GetRadius() const;
    void CalculateAABB(glm::vec2 e_position, float e_rotation) override;
};