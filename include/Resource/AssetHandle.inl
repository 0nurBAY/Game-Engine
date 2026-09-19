//AssetHandle.inl
#include "Resource/AssetHandle.h"
#pragma once

template<class A> AssetHandle<A>::AssetHandle(const std::string &name):name(name){

}
template<class A> const std::string &AssetHandle<A>::GetName() const{
    return name;
}
template<class A> bool AssetHandle<A>::IsValid() const{
    return !name.empty();
}
