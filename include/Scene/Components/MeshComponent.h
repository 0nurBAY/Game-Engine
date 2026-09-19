//MeshComponent.h

#pragma once
#include "Scene/Components/Component.h"
#include "Renderer/Mesh.h"
#include "Resource/AssetHandle.h"
#include <memory>

class MeshComponent: public Component
{
private:
    AssetHandle<Mesh> mesh;
public:
    MeshComponent(AssetHandle<Mesh> mesh);
    AssetHandle<Mesh> GetMesh() const;
};

