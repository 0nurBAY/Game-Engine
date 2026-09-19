//TestScript2.cpp
#include "Core/Script/TestScript2.h"
#include "Scene/Entity.h"
void TestScript2::Update(float deltatime){
    if(!arrived) walked+=deltatime;
    if(walked>=walktime){
        arrived = true;
        walked = 0.0f;
    }
    Decide(deltatime);
    auto* e = GetEntity();
    auto* animation = e->GetComponent<AnimationComponent>();
    if(arrived){
        if(lastdirection.x<0.0f&&lastdirection.y<0.0f)  {animation->RequestAnimation("BlackIdle_DownLeft" );}
        if(lastdirection.x<0.0f&&lastdirection.y>0.0f)  {animation->RequestAnimation("BlackIdle_UpLeft"   );}
        if(lastdirection.x<0.0f&&lastdirection.y==0.0f) {animation->RequestAnimation("BlackIdle_Left"     );}
        if(lastdirection.x==0.0f&&lastdirection.y<0.0f) {animation->RequestAnimation("BlackIdle_Down"     );}
        if(lastdirection.x==0.0f&&lastdirection.y>0.0f) {animation->RequestAnimation("BlackIdle_Up"       );}
        if(lastdirection.x>0.0f&&lastdirection.y<0.0f)  {animation->RequestAnimation("BlackIdle_DownRight");}
        if(lastdirection.x>0.0f&&lastdirection.y>0.0f)  {animation->RequestAnimation("BlackIdle_UpRight"  );}
        if(lastdirection.x>0.0f&&lastdirection.y==0.0f) {animation->RequestAnimation("BlackIdle_Right"    );}
        return;
    }

    auto* transform = e->GetComponent<TransformComp>();
    transform->position+=goal*500.0f*deltatime;
    if(goal.x<0.0f&&goal.y<0.0f)  {animation->RequestAnimation("BlackWalk_DownLeft" );}
    if(goal.x<0.0f&&goal.y>0.0f)  {animation->RequestAnimation("BlackWalk_UpLeft"   );}
    if(goal.x<0.0f&&goal.y==0.0f) {animation->RequestAnimation("BlackWalk_Left"     );}
    if(goal.x==0.0f&&goal.y<0.0f) {animation->RequestAnimation("BlackWalk_Down"     );}
    if(goal.x==0.0f&&goal.y>0.0f) {animation->RequestAnimation("BlackWalk_Up"       );}
    if(goal.x>0.0f&&goal.y<0.0f)  {animation->RequestAnimation("BlackWalk_DownRight");}
    if(goal.x>0.0f&&goal.y>0.0f)  {animation->RequestAnimation("BlackWalk_UpRight"  );}
    if(goal.x>0.0f&&goal.y==0.0f) {animation->RequestAnimation("BlackWalk_Right"    );}

    
}

void TestScript2::Decide(float deltatime){
    if(arrived){
        timepased+=deltatime;
        if(timepased<delay)return;
        timepased-=delay;
        std::random_device rd;
        std::mt19937 gen(rd());
        float x;
        float y;
        std::uniform_int_distribution<int> delaydist(10,30);
        std::uniform_int_distribution<int> walkdist(0,50);
        std::uniform_int_distribution<int> decidedist(-1,1);
        delay = (float)(delaydist(gen))/10;
        walktime = (float)(walkdist(gen))/10;
        do{
        x = decidedist(gen);
        y = decidedist(gen);
        }while (x == 0 && y == 0);
        goal = glm::vec2(x,y);
        if(goal.x!=0.0f&&goal.y!=0.0f) goal = normalize(goal);
        lastdirection = goal;
        arrived = false;
    }
}