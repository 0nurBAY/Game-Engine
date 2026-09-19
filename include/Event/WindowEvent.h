//WindowEvent.h

#pragma once
#include "Event/Event.h"

class WindowCloseEvent : public Event
{
public:
   EventType GetType() const override{
       return EventType::WindowClose;
   }
   static EventType StaticGetType() {
    return EventType::WindowClose;
   }
   int GetCategoryFlags() const override{
       return static_cast<int>(EventCategory::Application);
   }
};
 

class WindowResizeEvent : public Event
{
private:
    unsigned int width;
    unsigned int height;
public:
    WindowResizeEvent(unsigned int width,unsigned int height):width(width),height(height){}
    unsigned int GetWidth(){return width;}
    unsigned int GetHeight(){return height;}
    
    EventType GetType() const override{
        return EventType::WindowResize;
    }
    static EventType StaticGetType() {
     return EventType::WindowResize;
    }
    int GetCategoryFlags() const override{
        return static_cast<int>(EventCategory::Application);
    }
};