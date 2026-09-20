//TransformComponent.cpp
#include "Scene/Components/TransformComponent.h"

TransformComp::TransformComp(){}
TransformComp::TransformComp(glm::vec2 position, float rotation, glm::vec2 scale):
position(position),
rotation(rotation),
scale(scale){}