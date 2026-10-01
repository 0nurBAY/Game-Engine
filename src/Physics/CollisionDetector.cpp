//CollisionDetector.cpp
#include "Physics/CollisionDetector.h"

bool CollisionDetector::CircleVsCircle(ColliderShape* shape1, ColliderShape* shape2, glm::vec2 pos1, float rot1, glm::vec2 pos2, float rot2){
    glm::vec2 collider1Pos = pos1 + shape1->GetWorldTransform(pos1,rot1).position;
    glm::vec2 collider2Pos = pos2 + shape2->GetWorldTransform(pos2,rot2).position;
    float distanceSquared = glm::distance(collider1Pos, collider2Pos);
    float radius1 = dynamic_cast<CircleShape*>(shape1)->GetRadius();
    float radius2 = dynamic_cast<CircleShape*>(shape2)->GetRadius();
    float sumOfRadii = radius1 + radius2;
    return distanceSquared <= sumOfRadii * sumOfRadii;
}