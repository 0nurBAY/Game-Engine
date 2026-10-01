//CollisionDetector.h
#pragma once
#include "Physics/Physictypes.h"
#include "Physics/ColliderShape.h"
#include "Physics/BoxShape.h"
#include "Physics/CircleShape.h"

#include <glm/glm.hpp>
class CollisionDetector{

public:
    // static bool BoxVsBox      (ColliderShape* shape1, ColliderShape* shape2,  glm::vec2 pos1, float rot1, glm::vec2 pos2, float rot2);
    // static bool CircleVsBox   (ColliderShape* shape1, ColliderShape* shape2,  glm::vec2 pos1, float rot1, glm::vec2 pos2, float rot2);
    static bool CircleVsCircle   (ColliderShape* shape1, ColliderShape* shape2,  glm::vec2 pos1, float rot1, glm::vec2 pos2, float rot2);
};