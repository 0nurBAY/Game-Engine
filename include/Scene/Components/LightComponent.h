//LightComponent.h

#pragma once

#include "Scene/Components/Component.h"
#include <glm/glm.hpp>

class LightComponent:public Component
{
private:
    glm::vec4 color;
    float radius;
public:
    LightComponent(glm::vec4 color = glm::vec4(1.0f,1.0f,1.0f,1.0f),float radius = 200.0f);
    void SetColor (glm::vec4 new_color);
    void SetRadius(float new_radius);
    glm::vec4    GetColor() const;
    float       GetRadius() const;
};