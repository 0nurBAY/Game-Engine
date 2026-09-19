//Event.cpp
#include "Event/Event.h"


Event::~Event()
{
}

bool Event::IsinCategory(EventCategory category) const{ 
        return GetCategoryFlags() & static_cast<int>(category);
}
