//HitBoxDebuger.cpp

#include "Physics/HitBoxDebuger.h"
#include "Physics/Colliders.h"
#include <iostream>

void HitBoxDebug::DrawHitBox(ColliderShape *shape, Entity *entity,glm::vec4 color,DebugRenderer *debugrenderer){
    // std::cout<<"DrawHitBox Call\n";
    if(shape->GetShapeType() == ColliderType::Box) HitBoxDebug::DrawBox(shape,entity,color,debugrenderer);
    if(shape->GetShapeType() == ColliderType::Circle) HitBoxDebug::DrawCircle(shape,entity,color,debugrenderer);
}
void HitBoxDebug::DrawCircle(ColliderShape *shape, Entity *entity,glm::vec4 color,DebugRenderer *debugrenderer){
    // std::cout<<"DrawCircle Call\n";
    
    CircleShape* HitBox = dynamic_cast<CircleShape*>(shape);
    TransformComp* transformComp = entity->GetComponent<TransformComp>();
    Transform2D hitboxTransform = HitBox->GetWorldTransform(transformComp->position,transformComp->rotation);
    debugrenderer->DrawCircle(hitboxTransform.position,HitBox->GetRadius(),color);
}

void HitBoxDebug::DrawBox(ColliderShape *shape, Entity *entity,glm::vec4 color,DebugRenderer *debugrenderer){
    // std::cout<<"DrawBox Call\n";

    BoxShape* HitBox = dynamic_cast<BoxShape*>(shape);
    TransformComp* transformComp = entity->GetComponent<TransformComp>();
    Transform2D hitboxTransform = HitBox->GetWorldTransform(transformComp->position,transformComp->rotation);
    float cos = glm::cos(glm::radians(hitboxTransform.rotation));
    float sin = glm::sin(glm::radians(hitboxTransform.rotation));
    glm::vec2 halves = HitBox->Gethalves();
    glm::vec2 Coordinates[4] ={
        hitboxTransform.position+glm::vec2(halves.x*cos-halves.y*sin,halves.y*cos+halves.x*sin),
        hitboxTransform.position+glm::vec2(-halves.x*cos-halves.y*sin,halves.y*cos-halves.x*sin),
        hitboxTransform.position+glm::vec2(-halves.x*cos+halves.y*sin,-halves.y*cos-halves.x*sin),
        hitboxTransform.position+glm::vec2(halves.x*cos+halves.y*sin,-halves.y*cos+halves.x*sin)
    };
    for(int i=0; i<4; i++){
        if(i<3){
        debugrenderer->DrawLine(Coordinates[i],Coordinates[i+1],color);
        continue;
        }

        debugrenderer->DrawLine(Coordinates[i],Coordinates[0],color);
    }


}
