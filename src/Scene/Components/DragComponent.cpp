//DragComponent.cpp

#include "Event/EventDispatcher.h"
#include "Event/Event.h"
#include "Event/MouseEvent.h"
#include "Scene/Components/DragComponent.h"
#include "Scene/Entity.h"
#include "Scene/Scene.h"
#include <iostream>
void DragComponent::OnEvent(Event &event){
    EventDispatcher dispatcher(event);
    dispatcher.Dispatcher<MousePressedEvent>(
        [this](MousePressedEvent &event){
            std::cout << "Mouse button down: " << event.GetButton() <<"\n";
            if(event.GetButton() == 0)  {
                auto* cam = owner->GetScene()->GetEntityCamera();
                is_mouse_button=true;
                auto* tr = owner->GetComponent<TransformComp>();
                glm::vec2 npos = cam->ScreentoWorld(mpos);
                std::cout << "-------------------\ndistance check:\n" 
                <<"Entity: "<< tr->position.x <<","<<tr->position.y <<"\n"
                <<"Mouse: "<< npos.x <<","<<npos.y <<"\n"
                <<"Distance: "<< glm::distance(npos,tr->position) <<"\n-------------------\n\n";
                if(glm::distance(npos,tr->position) <= 50.0f) {
                    std::cout<< "holding the entity\n";
                    hold=true;
                    offset = tr->position - npos;
                }

            }
    });
    dispatcher.Dispatcher<MouseReleasedEvent>(
        [this](MouseReleasedEvent &event){
            std::cout << "Mouse button up\n";
            if(event.GetButton() == 0) {is_mouse_button=false;hold=false;}
    });
    dispatcher.Dispatcher<CursorMoveEvent>(
        [this](CursorMoveEvent &event){
            mpos.x = event.GetXPos();
            mpos.y = event.GetYPos();
    });
}

void DragComponent::Update(float dt){
    if(!hold)return;
    auto* cam = owner->GetScene()->GetEntityCamera();
    glm::vec2 npos = cam->ScreentoWorld(mpos);
    owner->GetComponent<TransformComp>()->position = glm::vec2(npos.x + offset.x,npos.y - offset.y);
}