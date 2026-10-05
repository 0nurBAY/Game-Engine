//BoxShape.h
#pragma once

#include "Physics/ColliderShape.h"

class BoxShape: public ColliderShape
{
private:
    glm::vec2 halfExtents;
    
public:
    BoxShape(float Width,float Height,glm::vec2 position,float rotation);
    void CalculateAABB(glm::vec2 e_position, float e_rotation) override;
    glm::vec2 Gethalves() const {return halfExtents;};
};
