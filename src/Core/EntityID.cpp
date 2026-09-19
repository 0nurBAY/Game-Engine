//EntityID.cpp
#include "Core/EntityID.h"

    
EntityID::EntityID(uint64_t id=0):id(id){}

uint64_t EntityID::Value() const{
    
    return id;
}

bool EntityID::operator==(const EntityID& other)const{
    
    return id == other.id;
}