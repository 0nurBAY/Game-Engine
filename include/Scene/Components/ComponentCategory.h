//ComponentCategory
#pragma once
#include <cstdint>
enum class CopmonentCategory: uint32_t{

    None = 0,
    Transform   = 1<<0,
    Rendering   = 1<<1,
    Camera      = 1<<2,
    Animation   = 1<<3,
    Script      = 1<<4,
    Physic      = 1<<5,
    Input       = 1<<6,
    State       = 1<<7,
    UI          = 1<<8,
    Particle    = 1<<9,
    Audio       = 1<<10,
    AI          = 1<<11
    
};

inline CopmonentCategory operator|(
    CopmonentCategory compa,
    CopmonentCategory compb
){
    return static_cast<CopmonentCategory>(
        static_cast<uint32_t>(compa) | static_cast<uint32_t>(compb)
    );
}


inline CopmonentCategory operator&(
    CopmonentCategory compa,
    CopmonentCategory compb
){
    return static_cast<CopmonentCategory>(
        static_cast<uint32_t>(compa) & static_cast<uint32_t>(compb)
    );
}

inline CopmonentCategory& operator&(
    CopmonentCategory& compa,
    CopmonentCategory compb
){
    compa = compa | compb;
    return compa;
}