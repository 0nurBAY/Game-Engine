//HandsScript.cpp

#include "Core/Script/HandsScript.h"
#include "Event/Event.h"
#include "Event/EventDispatcher.h"
#include "Event/KeyEvent.h"
#include <iostream>
void HandsScript::AddSign(char sign){
    signs.push(sign);
    
}
void HandsScript::ApplySignes(){
    std::cout <<"Signes:\n";
    for(;!signs.empty();signs.pop()){
        std::cout <<"\t" <<signs.front() <<"\n";
    }
}
void HandsScript::OnEvent(Event& event){
    

    EventDispatcher dispatcher(event);

    dispatcher.Dispatcher<KeyPressedEvent>(
        [this](KeyPressedEvent& event){
            int key = event.GetKey();
            if(key==87||key==65||key==83||key==68)return;
            // std::cout<<"1\n";
            if(key==257) {
                // std::cout<<"2\n";
                ApplySignes();
                return;
            }
            AddSign(key);
        }
    );

}