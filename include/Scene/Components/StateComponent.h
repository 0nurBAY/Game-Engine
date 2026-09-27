//StateComponent.h
#pragma once
#include "Scene/Components/Component.h"
#include "Event/StateEvent.h"
#include <string>
#include <vector>
#include <unordered_map>

enum class Retrigger_mod{
    Restart,
    Next,
    Random,
    Ignore
};

struct StateData{
public:
    int priority;
    float min_timer;
    bool complete;
    Retrigger_mod retrigger;
};
class StateComponent :public Component
{
private:
    std::string current_state;    
    std::vector<std::string> requests;
    std::unordered_map<std::string,StateData> states;
    bool state_complete = false;
    float time_passed = 0;
    void ChangeState(std::string state);
public:
    void OnCreate() override;
    StateComponent(std::string first_state);
    std::string GetState() const;
    void        Update(float dt) override;
    void        RequestState(std::string state);
    void        AddState(std::string state,int queue,float time,bool complete_info,Retrigger_mod retrigger_event);
    void        Complete();

};