
//MeshComponent.cpp

#include "Scene/Components/MeshComponent.h"
MeshComponent::MeshComponent(AssetHandle<Mesh> mesh) : mesh(mesh){}
AssetHandle<Mesh> MeshComponent::GetMesh() const{
    return mesh;
}