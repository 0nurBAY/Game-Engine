//UUID.cpp
#include "Core/UUID.h"
#include <iostream>
#include <random>

std::uint64_t EUUID::Value() const{
    return uuid;
}

bool EUUID::operator==(const EUUID& other) const{
    return uuid == other.uuid;
}

uint64_t EUUID::GetID(){
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
std::set<uint64_t> EUUID::GetAll(){
    return UUID_map;
}

void EUUID::RemoveID(std::uint64_t id){
    UUID_map.erase(id);
}