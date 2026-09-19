//Event.h
#pragma once

#include "Event/EventType.h"
#include "Event/EventCategory.h"
class Event
{
    
public:
    virtual ~Event() = default;
    virtual EventType GetType()     const = 0;
    virtual int GetCategoryFlags()  const = 0;

    bool IsinCategory(EventCategory category) const{ 
        return GetCategoryFlags() & static_cast<int>(category);
    }
    //Bunun mantığını kesin not al 
//Mantık: category'lerdeki bitleri Getflag'ten gelen bitler ile and gate e sokuyor sonra eğer flag varsa zaten sonuç 0'dan farklı geliyor bu yüzden true dönüyor

    bool done = false;

};
