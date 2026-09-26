//StateEvent.h

#pragma once

#include "Event/Event.h"
#include <string>
#include <iostream>
class StateChangeEvent : public Event
{
private:
    std::string state;
public:
    StateChangeEvent(std::string name):state(name){}
    std::string GetState()const{return state;}
    EventType GetType() const override{
       return EventType::StateChage;
    }
    static EventType StaticGetType() {
     return EventType::StateChage;
    }
    int GetCategoryFlags() const override{
       return static_cast<int>(EventCategory::Input)|static_cast<int>(EventCategory::Application)|static_cast<int>(EventCategory::State);
   }
};
