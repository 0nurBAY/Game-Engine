//StateComponent.cpp

#include "Scene/Components/StateComponent.h"
#include "Scene/Entity.h"
#include "Event/StateEvent.h"
#include <iostream>
std::string StateComponent::GetState() const{
    return state;
}

void StateComponent::SetState(std::string name){
    if(state==name)return;

    state = name;
    StateChangeEvent event(state);
    owner->OnEvent(event);

}