//Script.cpp
#include "Core/Script/Script.h"

void Script::SetEntity(Entity *entity){
    this->entity = entity;
}

void Script::SetInput(Input *input){
    this->input = input;
}

Entity *Script::GetEntity() const{
    return entity;
}

Input *Script::GetInput() const{
    return input;
}

