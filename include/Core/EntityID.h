//EntityID.h
#pragma once
#include <cstdint>

class EntityID
{
private:
    std::uint64_t id;
public:
    EntityID(std::uint64_t id);
    
    std::uint64_t Value() const;

    bool operator==(const EntityID& other)const;
};
