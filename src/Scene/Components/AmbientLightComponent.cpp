//AmbientLightComponent.cpp
#include "Scene/Components/AmbientLightComponent.h"

AmbientLightComponent::AmbientLightComponent(glm::vec4 color):color(color){}
void AmbientLightComponent::SetColor(glm::vec4 new_color){color = new_color;}
glm::vec4 AmbientLightComponent::GetColor() const{return color;}