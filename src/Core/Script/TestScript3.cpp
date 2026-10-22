//TestScript2.cpp
#include "Core/Script/TestScript3.h"
#include "Scene/Entity.h"
#include "Core/Input.h"
#include "Event/Events.h"
#include "Scene/Scene.h"
#include <iostream>
void TestScript3::Update(float deltatime){
    auto* e = GetEntity();
    auto* i = GetInput();
    auto* transform = e->GetComponent<TransformComp>();
    auto* rigidbody = e->GetComponent<RigidBodyComponent>();
    if(!arrived) walked+=deltatime;
    if(walked>=walktime){
        arrived = true;
        walked = 0.0f;
    }
    Decide(deltatime);
    auto* animation = e->GetComponent<AnimationComponent>();
    auto* state     = e->GetComponent<StateComponent>();
    
    // if(i->IsMouseButtonDown(GLFW_MOUSE_BUTTON_1)){
    //     std::cout << "Force required\n";
    //     double mx = i->GetMouseX();
    //     double my = i->GetMouseY();
    //     auto* camera = e->GetScene()->GetEntityCamera();
    //     glm::vec2 npos = camera->ScreentoWorld(glm::vec2(mx,my));
    //     std::cout << "Force has applied: " << (npos.x-transform->position.x)*0.1f << "," << (npos.y-transform->position.y)*0.1f << "\n";
    //     rigidbody->ApplyForce((npos-transform->position)*10.0f);
    //     return;
    // }
    
    if(arrived){
        state->RequestState("Idle");
        rigidbody->SetVelocity(glm::vec2(0.0f));
        return;
    }
    

    
    glm::vec2 vel = rigidbody->GetVelocity();
    glm::vec2 target = goal*500.0f;
    glm::vec2 difference = target - vel;
    float difference_len = glm::length(difference);
    float step = (glm::length(goal)>0.0f)? 2000.0f * deltatime: 0.0f;
    vel = (difference_len > step)? vel + difference / difference_len * step : target;
    rigidbody->SetVelocity(vel);

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

void TestScript3::Decide(float deltatime){
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
void TestScript3::CollisionDecide(glm::vec2 new_goal){
        // new_goal = glm::normalize(new_goal);
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
        goal = new_goal;
        if(goal.x!=0.0f&&goal.y!=0.0f) goal = normalize(goal);
        lastdirection = goal;
        arrived = false;
        timepased = 0;
        
}
void TestScript3::OnEvent(Event &event){
    EventDispatcher dispatcher(event);
    // dispatcher.Dispatcher<MousePressedEvent>(
    //     [this](MousePressedEvent& event){
    //         auto state = this->GetEntity()->GetComponent<StateComponent>();
    //         state->RequestState("Attack");
    //     }
    // );
    dispatcher.Dispatcher<CollisionEvent>(
        [this](CollisionEvent& event){
            CollisionDecide(event.GetDir());
            // std::cout<< "Entity " << this->GetEntity()->GetName() << " Colaps with "<< event.GetOther() <<"\n";
        }
    );
}