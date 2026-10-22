//TransformComponent.cpp
#include "Scene/Components/TransformComponent.h"

TransformComp::TransformComp(){}

CopmonentCategory TransformComp::GetCategory() const{
    return (CopmonentCategory::Transform);
}

TransformComp::TransformComp(glm::vec2 position, float rotation, glm::vec2 scale):
position(position),
rotation(rotation),
scale(scale){}

glm::vec2 TransformComp::GetMinMaxX() const{
    return glm::vec2(position.x-scale.x,position.x+scale.x);
}

glm::vec2 TransformComp::GetMinMaxY() const{
    return glm::vec2(position.y-scale.y,position.y+scale.y);
}