//UUID.cpp
#include "Core/UUID.h"
#include <iostream>
#include <random>

std::uint64_t UUID::Value() const{
    return uuid;
}

bool UUID::operator==(const UUID& other) const{
    return uuid == other.uuid;
}

uint64_t UUID::GetID(){
    while (true){
    static std::random_device rd;

    static std::mt19937_64 generator(rd());
    uuid = generator();

    auto cid = UUID_map.find(uuid);
    if (cid != UUID_map.end()){}
    else{
        UUID_map.insert(uuid);
        return uuid;
    };
    }
}
std::set<uint64_t> UUID::GetAll(){
    return UUID_map;
}

void UUID::RemoveID(std::uint64_t id){
    UUID_map.erase(id);
}