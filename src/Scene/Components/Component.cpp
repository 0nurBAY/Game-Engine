//Component.h
#include "Scene/Components/Component.h"



void Component::AddOwner(Entity* own)
{
    owner = own;
}
Component::~Component(){}
