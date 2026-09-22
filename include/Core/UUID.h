//UUID.h
#pragma once
#include <cstdint>
#include <set>
class EUUID
{
private:
    std::uint64_t uuid;
    std::set<uint64_t> UUID_map;

public:
    uint64_t GetID();

    std::uint64_t Value() const;

    bool operator==(const EUUID& other) const;

    std::set<uint64_t> GetAll();

    void RemoveID(std::uint64_t id);
};