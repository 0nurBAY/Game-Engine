//RendererComponent.cpp

#include "Scene/Components/RendererComponent.h"
RendererComponent::RendererComponent(unsigned int layer,float new_z):layer(layer),z(z){}
void RendererComponent::SetLayer(unsigned int new_layer){
    layer = new_layer;
}
void RendererComponent::SetZ(float new_z){
    z = new_z;
}
unsigned int RendererComponent::GetLayer(){
    return layer;
}
float RendererComponent::GetZ(){
    return z;
}