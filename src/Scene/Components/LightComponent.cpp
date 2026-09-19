//LightComponent.h
#include "Scene/Components/LightComponent.h"

LightComponent::LightComponent(glm::vec4 color, float radius):
color(color),radius(radius)
{}

void LightComponent::SetColor(glm::vec4 new_color){
    color = new_color;
}
void LightComponent::SetRadius(float new_radius){
    radius = new_radius;
}
glm::vec4 LightComponent::GetColor()const{
    return color;
}
float LightComponent::GetRadius()const{
    return radius;
}