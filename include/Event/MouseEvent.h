//MouseEvent.h

#pragma once
#include "Event/Event.h"
class MousePressedEvent : public Event
{ 
private:
   int button;
public:
    MousePressedEvent(int button):button(button){}
    int GetButton(){
        return button;
    }
    EventType GetType() const override{
        return EventType::MousePressed;
    }
    static EventType StaticGetType() {
     return EventType::MousePressed;
    }
    int GetCategoryFlags() const override{
     return static_cast<int>(EventCategory::Input)|static_cast<int>(EventCategory::Mouse)|static_cast<int>(EventCategory::MouseButton);
    }
};

class MouseReleasedEvent : public Event
{
private:
   int button;
public:
   MouseReleasedEvent(int button):button(button){}
   int GetButton(){
       return button;
   }
   EventType GetType() const override{
       return EventType::MouseReleased;
   }
   
   static EventType StaticGetType() {
    return EventType::MouseReleased;
   }
   int GetCategoryFlags() const override{
       return static_cast<int>(EventCategory::Input)|static_cast<int>(EventCategory::Mouse)|static_cast<int>(EventCategory::MouseButton);
   }
};
 
class CursorMoveEvent : public Event
{
private:
    double xpos;
    double ypos;
public:
    CursorMoveEvent(double xpos,double ypos):xpos(xpos),ypos(ypos){}
    double GetXPos(){return xpos;}
    double GetYPos(){return ypos;}
    EventType GetType() const override{
       return EventType::MouseMoved;
    }
    static EventType StaticGetType() {
     return EventType::MouseMoved;
    }
    int GetCategoryFlags() const override{
       return static_cast<int>(EventCategory::Input)|static_cast<int>(EventCategory::Mouse);
   }
};

class ScrollEvent : public Event
{

private:
    double xoffset;
    double yoffset;
public:
    ScrollEvent(double xoffset,double yoffset):xoffset(xoffset),yoffset(yoffset){}
    double GetXOffset(){return xoffset;}
    double GetYOffset(){return yoffset;}
    
    EventType GetType() const override{
       return EventType::MouseScrolled;
    }
    static EventType StaticGetType() {
     return EventType::MouseScrolled;
    }
    int GetCategoryFlags() const override{
       return static_cast<int>(EventCategory::Input)|static_cast<int>(EventCategory::Mouse);
   }
};