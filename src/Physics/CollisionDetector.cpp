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
    ColliderResult res = {distance <= sumOfRadii,normal,sumOfRadii-distance,collider1Pos,collider2Pos,contact1,contact2};
    res.radius1 = radius1;
    res.radius2 = radius2;
    return res;

}

ColliderResult CollisionDetector::BoxVsBox(ColliderShape* shape1, ColliderShape* shape2, glm::vec2 pos1, float rot1, glm::vec2 pos2, float rot2)
{   
    auto* shapeA = dynamic_cast<BoxShape*>(shape1);
    auto* shapeB = dynamic_cast<BoxShape*>(shape2);
    Transform2D A = shapeA->GetWorldTransform(pos1,rot1);
    Transform2D B = shapeB->GetWorldTransform(pos2,rot2);
    float cosA = glm::cos(glm::radians(A.rotation));
    float sinA = glm::sin(glm::radians(A.rotation));
    float cosB = glm::cos(glm::radians(B.rotation));
    float sinB = glm::sin(glm::radians(B.rotation));
    glm::vec2 Axixes[4] ={
        glm::vec2(cosA,sinA),
        glm::vec2(cosB,sinB),
        glm::vec2(-sinA,cosA),
        glm::vec2(-sinB,cosB)
    };
    glm::vec2 CoordinatesA[4] ={
        A.position+glm::vec2(shapeA->Gethalves().x*cosA-shapeA->Gethalves().y*sinA,shapeA->Gethalves().y*cosA+shapeA->Gethalves().x*sinA),
        A.position+glm::vec2(-shapeA->Gethalves().x*cosA-shapeA->Gethalves().y*sinA,shapeA->Gethalves().y*cosA-shapeA->Gethalves().x*sinA),
        A.position+glm::vec2(shapeA->Gethalves().x*cosA+shapeA->Gethalves().y*sinA,-shapeA->Gethalves().y*cosA+shapeA->Gethalves().x*sinA),
        A.position+glm::vec2(-shapeA->Gethalves().x*cosA+shapeA->Gethalves().y*sinA,-shapeA->Gethalves().y*cosA-shapeA->Gethalves().x*sinA)
    };
    
    glm::vec2 CoordinatesB[4] ={
        B.position+glm::vec2(shapeB->Gethalves().x*cosB-shapeB->Gethalves().y*sinB,shapeB->Gethalves().y*cosB+shapeB->Gethalves().x*sinB),
        B.position+glm::vec2(-shapeB->Gethalves().x*cosB-shapeB->Gethalves().y*sinB,shapeB->Gethalves().y*cosB-shapeB->Gethalves().x*sinB),
        B.position+glm::vec2(shapeB->Gethalves().x*cosB+shapeB->Gethalves().y*sinB,-shapeB->Gethalves().y*cosB+shapeB->Gethalves().x*sinB),
        B.position+glm::vec2(-shapeB->Gethalves().x*cosB+shapeB->Gethalves().y*sinB,-shapeB->Gethalves().y*cosB-shapeB->Gethalves().x*sinB)
    };
    float min_penetration = FLT_MAX;
    glm::vec2 normal;
    bool collision = true;
    for(glm::vec2& axis:Axixes){
        float minA=FLT_MAX;
        float maxA=-FLT_MAX;
        float minB=FLT_MAX;
        float maxB=-FLT_MAX;
        for(int i=0; i<4;i++){
            glm::vec2 a = CoordinatesA[i];
            glm::vec2 b = CoordinatesB[i];
            float projection =glm::dot(a,axis);
            minA = std::min(projection,minA);
            maxA = std::max(projection,maxA);
            
            projection =glm::dot(b,axis);
            minB = std::min(projection,minB);
            maxB = std::max(projection,maxB);
        }
        float overlap = std::min(maxA,maxB) - std::max(minA,minB);
        if(overlap<0) {
            collision = false;
            break;}
        if(min_penetration>overlap){
            min_penetration = overlap;
            normal = axis;
        }
    }
    if(!collision) return{false};
    if(glm::dot(normal,(B.position-A.position))<0) normal = -normal;
    ColliderResult res = {true,normal,min_penetration,A.position,B.position};
    res.halfextend1 = shapeA->Gethalves();
    res.halfextend2 = shapeB->Gethalves();
    return res;


}