//ScriptComponent.inl

#pragma once

template<class T> T *ScriptComponent::GetScript(){
    return dynamic_cast<T*>(script.get());
}