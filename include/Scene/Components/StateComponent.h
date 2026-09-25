//StateComponent.h
#pragma once
#include "Scene/Components/Component.h"
#include "Event/StateEvent.h"
#include <string>
class StateComponent :public Component
{
private:
    std::string state;    
public:
    std::string GetState() const;
    void        SetState(std::string name);
};