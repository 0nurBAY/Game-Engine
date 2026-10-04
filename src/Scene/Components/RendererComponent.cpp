//RendererComponent.cpp

#include "Scene/Components/RendererComponent.h"
RendererComponent::RendererComponent(unsigned int layer,float depht_offset):layer(layer),depht_offset(depht_offset){}
void RendererComponent::SetLayer(unsigned int new_layer){
    layer = new_layer;
}
void RendererComponent::SetOffset(float depht_offset){
    this->depht_offset = depht_offset;
}
unsigned int RendererComponent::GetLayer(){
    return layer;
}
float RendererComponent::GetOffset(){
    return depht_offset;
}

CopmonentCategory RendererComponent::GetCategory() const{
    return (CopmonentCategory::Rendering);
}