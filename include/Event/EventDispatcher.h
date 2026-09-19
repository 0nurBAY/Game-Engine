//EventDispatcher.h

#pragma once
#include "Event/Event.h"
class EventDispatcher
{
private:
    Event& event;
public:
    EventDispatcher(Event& event):event(event) {};
    template<typename T, typename F> bool Dispatcher(const F& func){
        if (event.GetType() == T::StaticGetType()){
            func(static_cast<T&>(event));
            event.done = true;
            return true;
        }
        return false;
    }
};
