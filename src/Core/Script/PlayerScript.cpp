//PlayerScript.cpp
#include "Core/Script/PlayerScript.h"
#include "Scene/Entity.h"
#include "Core/Input.h"
#include "Event/Events.h"
#include <iostream>
void PlayerScript::Update(float deltatime){
    auto* e = GetEntity();
    auto* i = GetInput();
    auto* transform = e->GetComponent<TransformComp>();
    auto* animation = e->GetComponent<AnimationComponent>();
    auto* state     = e->GetComponent<StateComponent>();
    float spd = 500.0f;
    glm::vec2 direction(0.0f,0.0f);
    if(i->IsKeyDown(GLFW_KEY_W)){direction.y +=1.0f;}
    if(i->IsKeyDown(GLFW_KEY_A)){direction.x -=1.0f;}
    if(i->IsKeyDown(GLFW_KEY_S)){direction.y -=1.0f;}
    if(i->IsKeyDown(GLFW_KEY_D)){direction.x +=1.0f;}
    if (glm::length(direction) > 0.0f)  direction = glm::normalize(direction);
    transform->position+=direction*spd*deltatime;
    
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
    // EventDispatcher dispatcher(event);
    // dispatcher.Dispatcher<MousePressedEvent>(
    //     [this](MousePressedEvent& event){
    //         auto state = this->GetEntity()->GetComponent<StateComponent>();
    //         state->RequestState("Attack");
    //     }
    // );
}