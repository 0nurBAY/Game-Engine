//PlayerScript.cpp
#include "Core/Script/PlayerScript.h"
#include "Scene/Entity.h"
#include "Core/Input.h"
#include "Event/Events.h"
#include "Scene/Scene.h"
#include <iostream>
void PlayerScript::Update(float deltatime){
    auto* e = GetEntity();
    auto* i = GetInput();
    auto* transform = e->GetComponent<TransformComp>();
    auto* animation = e->GetComponent<AnimationComponent>();
    auto* state     = e->GetComponent<StateComponent>();
    auto* rigidbody = e->GetComponent<RigidBodyComponent>();
    float spd = 1000.0f;
    glm::vec2 direction(0.0f,0.0f);
    float rotation = 0.0f;

    // if(i->IsMouseButtonDown(GLFW_MOUSE_BUTTON_2)){
    //     double mx = i->GetMouseX();
    //     double my = i->GetMouseY();
    //     auto* camera = e->GetScene()->GetEntityCamera();
    //     glm::vec2 npos = camera->ScreentoWorld(glm::vec2(mx,my));
    //     // std::cout << "Force has applied: " << (npos.x-transform->position.x)*0.1f << "," << (npos.y-transform->position.y)*0.1f << "\n";
    //     rigidbody->ApplyForce((npos-transform->position)*10.0f);
    // }
    
    if(i->IsKeyDown(GLFW_KEY_W)){direction.y +=1.0f;}
    if(i->IsKeyDown(GLFW_KEY_A)){direction.x -=1.0f;}
    if(i->IsKeyDown(GLFW_KEY_S)){direction.y -=1.0f;}
    if(i->IsKeyDown(GLFW_KEY_D)){direction.x +=1.0f;}
    if(i->IsKeyDown(GLFW_KEY_Z)){rotation -=1.0f;}
    if(i->IsKeyDown(GLFW_KEY_X)){rotation +=1.0f;}
    if (glm::length(direction) > 0.0f)  direction = glm::normalize(direction);
    
    glm::vec2 vel = rigidbody->GetVelocity();
    glm::vec2 target = direction *spd;
    glm::vec2 difference = target - vel;
    float difference_len = glm::length(difference);
    float step = (glm::length(direction)>0.0f)? 2000.0f * deltatime: 0.0f;
    transform->rotation += rotation;
    vel = (difference_len > step)? vel + difference / difference_len * step : target;
    rigidbody->SetVelocity(vel);

    if(direction.x<0.0f&&direction.y<0.0f)  {animation->SetDirection(Directions::DOWNLEFT);}
    if(direction.x<0.0f&&direction.y>0.0f)  {animation->SetDirection(Directions::UPLEFT);}
    if(direction.x<0.0f&&direction.y==0.0f) {animation->SetDirection(Directions::LEFT);}
    if(direction.x==0.0f&&direction.y<0.0f) {animation->SetDirection(Directions::DOWN);}
    if(direction.x==0.0f&&direction.y>0.0f) {animation->SetDirection(Directions::UP);}
    if(direction.x>0.0f&&direction.y<0.0f)  {animation->SetDirection(Directions::DOWNRIGHT);}
    if(direction.x>0.0f&&direction.y>0.0f)  {animation->SetDirection(Directions::UPRIGHT);}
    if(direction.x>0.0f&&direction.y==0.0f) {animation->SetDirection(Directions::RIGHT);}
    if(direction.x==0.0f&&direction.y==0.0f){state->RequestState("Idle");}
    else{state->RequestState("Walk");}

}
void PlayerScript::OnEvent(Event &event){
    
    EventDispatcher dispatcher(event);
    dispatcher.Dispatcher<MousePressedEvent>(
        [this](MousePressedEvent& event){
            if(event.GetButton()==GLFW_MOUSE_BUTTON_2) return;
            auto state = this->GetEntity()->GetComponent<StateComponent>();
            state->RequestState("Attack");
        }
    );
    dispatcher.Dispatcher<CollisionEvent>(
        [this](CollisionEvent& event){
            // std::cout<< "Entity " << this->GetEntity()->GetName() << " Colaps with "<< event.GetOther() << "\n";
            auto state = this->GetEntity()->GetComponent<StateComponent>();
            state->RequestState("Collision");
        }
    );
}