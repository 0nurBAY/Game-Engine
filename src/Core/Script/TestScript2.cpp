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
    auto* state     = e->GetComponent<StateComponent>();
    if(arrived){
        state->RequestState("Idle");
        return;
    }

    auto* transform = e->GetComponent<TransformComp>();
    transform->position+=goal*500.0f*deltatime;
    if(goal.x<0.0f&&goal.y<0.0f)  {animation->SetDirection(Directions::DOWNLEFT);}
    if(goal.x<0.0f&&goal.y>0.0f)  {animation->SetDirection(Directions::UPLEFT);}
    if(goal.x<0.0f&&goal.y==0.0f) {animation->SetDirection(Directions::LEFT);}
    if(goal.x==0.0f&&goal.y<0.0f) {animation->SetDirection(Directions::DOWN);}
    if(goal.x==0.0f&&goal.y>0.0f) {animation->SetDirection(Directions::UP);}
    if(goal.x>0.0f&&goal.y<0.0f)  {animation->SetDirection(Directions::DOWNRIGHT);}
    if(goal.x>0.0f&&goal.y>0.0f)  {animation->SetDirection(Directions::UPRIGHT);}
    if(goal.x>0.0f&&goal.y==0.0f) {animation->SetDirection(Directions::RIGHT);}
    state->RequestState("Walk");
    
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