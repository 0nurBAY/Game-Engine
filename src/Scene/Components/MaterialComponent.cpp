//MaterialComponent.cpp

#include "Scene/Components/MaterialComponent.h"


MaterialComponent::MaterialComponent(AssetHandle<Material> material):material(material)
{
}
AssetHandle<Material> MaterialComponent::GetMaterial() const{
    return material;
}