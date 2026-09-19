//MaterialComponent.h
#include "Scene/Components/Component.h"
#include "Renderer/Material.h"
#include "Resource/AssetHandle.h"
#include <memory>
class MaterialComponent : public Component
{
private:
    AssetHandle<Material> material;
public:
    MaterialComponent(AssetHandle<Material> material);
    
    AssetHandle<Material> GetMaterial() const;
};
