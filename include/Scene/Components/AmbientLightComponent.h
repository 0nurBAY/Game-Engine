//AmbientLightComponent.h

#pragma once
#include "Scene/Components/Component.h"
#include <glm/glm.hpp>

class AmbientLightComponent:public Component
{
private:
    glm::vec4 color;
public:
    AmbientLightComponent(glm::vec4 color = glm::vec4(1.0f,1.0f,1.0f,1.0f));
    void        SetColor (glm::vec4 new_color);
    glm::vec4   GetColor() const;
};