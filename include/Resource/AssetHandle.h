//AssetHandle.h
#pragma once

#include "Core/UUID.h"
#include "Core/EntityID.h"

#include <string>

template<typename A> class AssetHandle
{
private:
    // UUID uuid;
    // EntityID id;
    std::string name;
public:
    AssetHandle() = default;
    AssetHandle(const std::string& name);
    
    const std::string& GetName() const;
    bool IsValid() const;
};

#include "Resource/AssetHandle.inl"


