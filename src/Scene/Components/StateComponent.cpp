//StateComponent.cpp

#include "Scene/Components/StateComponent.h"
#include "Scene/Entity.h"
#include "Event/StateEvent.h"
#include <iostream>

StateComponent::StateComponent(std::string first_state):current_state(first_state){
}
void StateComponent::OnCreate(){
    ChangeState(current_state);
}


std::string StateComponent::GetState() const{
    return current_state;
}

void StateComponent::RequestState(std::string state){
    // std::cout<<owner->GetName()<<" State_Changed to "<<name<<"\n";
    // if(state==name)return;
    requests.push_back(state);

    // std::cout << "REQUEST: " << state << "\n";
}
void StateComponent::Update(float dt){
    time_passed+=dt;
    if(requests.empty())return;
    auto st = states.find(current_state);
    if(st == states.end()) throw std::runtime_error(owner->GetName() + "StateComponent::Update  invalid state: " + current_state);
    auto& data = st->second;

    if(requests.size()==1) {
        if(requests[0] == current_state && data.retrigger == Retrigger_mod::Ignore) {requests.clear(); return;}
        st = states.find(requests[0]);
        if(st == states.end()) throw std::runtime_error(owner->GetName() + "StateComponent::Update  invalid state: " + current_state);
        auto& data2 = st->second;
        if(data2.priority>data.priority) {ChangeState(requests[0]); return;}
        if(data.complete==true && (state_complete==false || data.min_timer>time_passed)) {requests.clear(); return;}
        ChangeState(requests[0]);
        return;
    }
    int highest_priority = -1;
    std::string hp_state;
    for(auto& state:requests){
        auto st2 = states.find(state);
        if(st2==states.end())continue; 
        if(highest_priority>st2->second.priority) continue;
        highest_priority = st2->second.priority;
        hp_state = state;
    }
    if(hp_state.empty()) throw std::runtime_error(owner->GetName() + "StateComponent::Update empty hp_state");
    if(hp_state == current_state && data.retrigger == Retrigger_mod::Ignore) {requests.clear(); return;}
    st = states.find(hp_state);
    if(st == states.end()) throw std::runtime_error(owner->GetName() + "StateComponent::Update  invalid state: " + current_state);
    auto& data2 = st->second;
    if(data2.priority>data.priority) {ChangeState(hp_state); return;}
    if(data.complete==true && (state_complete==false || data.min_timer>time_passed)) {requests.clear(); return;}
    ChangeState(hp_state);
}

void StateComponent::AddState(std::string state, int queue, float time,bool complete_info,Retrigger_mod retrigger_event){
    states[state] = {queue,time,complete_info,retrigger_event};
}
void StateComponent::ChangeState(std::string state){

    // Yeni state'in verilerini bul
    auto it = states.find(state);

    if(it == states.end()){
        std::cout
            << "\n[StateComponent] ERROR - CHANGE STATE\n"
            << "  Entity       : " << owner->GetName() << "\n"
            << "  Requested    : " << state << "\n"
            << "  Error        : State does not exist\n"
            << "########################################\n";

        throw std::runtime_error(
            owner->GetName() +
            "StateComponent::ChangeState invalid state: " +
            state
        );
    }

    auto& data = it->second;


    std::cout
        << "\n========================================\n"
        << "[StateComponent] STATE CHANGED\n"
        << "  Entity       : " << owner->GetName() << "\n"
        << "  Previous     : " << current_state << "\n"
        << "  New State    : " << state << "\n"
        << "\n"
        << "  --- State Data ---\n"
        << "  Priority     : " << data.priority << "\n"
        << "  Min Timer    : " << data.min_timer << "\n"
        << "  Complete     : " << (data.complete ? "true" : "false") << "\n"
        << "  Retrigger    : " << static_cast<int>(data.retrigger) << "\n"
        << "\n"
        << "  State Complete : false\n"
        << "  Time Passed    : 0\n"
        << "========================================\n";


    current_state = state;

    StateChangeEvent event(state);

    // Yeni state başladığı için henüz tamamlanmış değildir.
    state_complete = false;

    // Yeni state'in timer'ı sıfırlanır.
    time_passed = 0;

    // Eski state'e ait bekleyen requestler temizlenir.
    requests.clear();

    // State değişikliğini diğer componentlere bildir.
    owner->OnEvent(event);
}
void StateComponent::Complete(){
    // std::cout << "[StateComponent] COMPLETE | Entity: "
    //           << owner->GetName()
    //           << " | State: "
    //           << current_state
    //           << "\n";

    state_complete = true;
    
    // std::cout << "[StateComponent] COMPLETE | Entity: "
    //           << owner->GetName()
    //           << " | State: "
    //           << current_state
    //           << "\n";

}