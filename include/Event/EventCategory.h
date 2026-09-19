//EventCategory.h

#pragma once

enum class EventCategory{
    
    None            = 0,
    Input           = 1<<0,
    Keyboard        = 1<<1,
    Mouse           = 1<<2,
    MouseButton     = 1<<3,
    Application     = 1<<4

};