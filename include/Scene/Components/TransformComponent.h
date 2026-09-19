//Transform.h
#pragma once
#include "Scene/Components/Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class TransformComp: public Component
{       
public:
    TransformComp(/* args */);
    glm::vec2 position;
    float rotation;
    glm::vec2 scale;
};
