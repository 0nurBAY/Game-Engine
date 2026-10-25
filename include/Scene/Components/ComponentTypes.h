#pragma once
#include <cstdint>

inline uint32_t NextComponentID(){
    static uint32_t counter = 0;
    return counter++;
}

template<typename T> uint32_t ComponentTypeID(){
    static const uint32_t id = NextComponentID();
    return id;
}