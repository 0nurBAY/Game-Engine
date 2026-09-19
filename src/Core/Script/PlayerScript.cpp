//PlayerScript.cpp
#include "Core/Script/PlayerScript.h"
#include "Scene/Entity.h"
#include "Core/Input.h"
#include <iostream>
void PlayerScript::Update(float deltatime){
    auto* e = GetEntity();
    auto* i = GetInput();
    auto* transform = e->GetComponent<TransformComp>();
    auto* animation = e->GetComponent<AnimationComponent>();
    float spd = 500.0f;
    glm::vec2 direction(0.0f,0.0f);
    if(i->IsKeyDown(GLFW_KEY_W)){direction.y +=1.0f;}
    if(i->IsKeyDown(GLFW_KEY_A)){direction.x -=1.0f;}
    if(i->IsKeyDown(GLFW_KEY_S)){direction.y -=1.0f;}
    if(i->IsKeyDown(GLFW_KEY_D)){direction.x +=1.0f;}
    if (glm::length(direction) > 0.0f)  direction = glm::normalize(direction);
    transform->position+=direction*spd*deltatime;
    if(direction.x<0.0f&&direction.y<0.0f)  {animation->RequestAnimation("PlayerWalk_DownLeft" );}
    if(direction.x<0.0f&&direction.y>0.0f)  {animation->RequestAnimation("PlayerWalk_UpLeft"   );}
    if(direction.x<0.0f&&direction.y==0.0f) {animation->RequestAnimation("PlayerWalk_Left"     );}
    if(direction.x==0.0f&&direction.y<0.0f) {animation->RequestAnimation("PlayerWalk_Down"     );}
    if(direction.x==0.0f&&direction.y>0.0f) {animation->RequestAnimation("PlayerWalk_Up"       );}
    if(direction.x>0.0f&&direction.y<0.0f)  {animation->RequestAnimation("PlayerWalk_DownRight");}
    if(direction.x>0.0f&&direction.y>0.0f)  {animation->RequestAnimation("PlayerWalk_UpRight"  );}
    if(direction.x>0.0f&&direction.y==0.0f) {animation->RequestAnimation("PlayerWalk_Right"    );}
    if(direction.x==0.0f&&direction.y==0.0f){
        if(lastdirection.x<0.0f&&lastdirection.y<0.0f)  {animation->RequestAnimation("PlayerIdle_DownLeft" );}
        if(lastdirection.x<0.0f&&lastdirection.y>0.0f)  {animation->RequestAnimation("PlayerIdle_UpLeft"   );}
        if(lastdirection.x<0.0f&&lastdirection.y==0.0f) {animation->RequestAnimation("PlayerIdle_Left"     );}
        if(lastdirection.x==0.0f&&lastdirection.y<0.0f) {animation->RequestAnimation("PlayerIdle_Down"     );}
        if(lastdirection.x==0.0f&&lastdirection.y>0.0f) {animation->RequestAnimation("PlayerIdle_Up"       );}
        if(lastdirection.x>0.0f&&lastdirection.y<0.0f)  {animation->RequestAnimation("PlayerIdle_DownRight");}
        if(lastdirection.x>0.0f&&lastdirection.y>0.0f)  {animation->RequestAnimation("PlayerIdle_UpRight"  );}
        if(lastdirection.x>0.0f&&lastdirection.y==0.0f) {animation->RequestAnimation("PlayerIdle_Right"    );}
    }
    if(direction!=glm::vec2(0.0f,0.0f))lastdirection = direction;
}