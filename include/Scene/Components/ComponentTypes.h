#pragma once
#include <cstdint>

// Tek, ortak sayaç
inline uint32_t NextComponentID()
{
    static uint32_t counter = 0;
    return counter++;
}

// Her T için ayrı bir fonksiyon, ayrı bir static id
template<typename T>
uint32_t ComponentTypeID()
{
    static const uint32_t id = NextComponentID();
    return id;
}