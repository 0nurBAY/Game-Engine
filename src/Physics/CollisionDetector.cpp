//CollisionDetector.cpp
#include "Physics/CollisionDetector.h"

ColliderResult CollisionDetector::CircleVsCircle(ColliderShape* shape1, ColliderShape* shape2, glm::vec2 pos1, float rot1, glm::vec2 pos2, float rot2){
    glm::vec2 collider1Pos = shape1->GetWorldTransform(pos1,rot1).position;
    glm::vec2 collider2Pos = shape2->GetWorldTransform(pos2,rot2).position;
    glm::vec2 normal = glm::normalize(collider2Pos - collider1Pos);
    float distance = glm::distance(collider1Pos, collider2Pos);
    float radius1 = dynamic_cast<CircleShape*>(shape1)->GetRadius();
    float radius2 = dynamic_cast<CircleShape*>(shape2)->GetRadius();
    float sumOfRadii = radius1 + radius2;
    glm::vec2 contact1 = (radius1 * normal) + collider1Pos;
    glm::vec2 contact2 = (radius2 * -normal) + collider2Pos;
    return {distance <= sumOfRadii,normal,contact1,contact2,sumOfRadii-distance,collider1Pos,collider2Pos,radius1,radius2};

}