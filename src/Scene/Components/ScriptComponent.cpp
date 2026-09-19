//ScriptComponent.cpp
#include "Scene/Components/ScriptComponent.h"
#include <iostream>

ScriptComponent::ScriptComponent(std::unique_ptr<Script> script):script(std::move(script)){
}

void ScriptComponent::Update(float dt){
    if(!script)return;
    script->Update(dt);
}
void ScriptComponent::SetEntity(Entity *entity){
    if(!script)return;
    script->SetEntity(entity);
}

void ScriptComponent::SetInput(Input *input){
    if(!script)return;
    script->SetInput(input);
}

void ScriptComponent::OnCreate(){
    if(!script)return;
    script->OnCreate();
}

void ScriptComponent::OnDestroy(){
    if(!script)return;
    script->OnDestroy();
}
void ScriptComponent::OnEvent(Event& event){
    if(!script)return;
    script->OnEvent(event);
}