//KeyEvent.h

#pragma once
#include "Event/Event.h"
class KeyPressedEvent : public Event
{
private:
   int key;
public:
   KeyPressedEvent(int key):key(key){}
   int GetKey(){
       return key;
   }
   EventType GetType() const override{
       return EventType::KeyPressed;
   }
   static EventType StaticGetType() {
    return EventType::KeyPressed;
   }
   int GetCategoryFlags() const override{
       return static_cast<int>(EventCategory::Input)|static_cast<int>(EventCategory::Keyboard);
   }
};

class KeyReleasedEvent : public Event
{
private:
   int key;
public:
   KeyReleasedEvent(int key):key(key){}
   int GetKey(){
       return key;
   }
   EventType GetType() const override{
       return EventType::KeyReleased;
   }
   static EventType StaticGetType() {
    return EventType::KeyReleased;
   }
   int GetCategoryFlags() const override{
       return static_cast<int>(EventCategory::Input)|static_cast<int>(EventCategory::Keyboard);
   }
};
 