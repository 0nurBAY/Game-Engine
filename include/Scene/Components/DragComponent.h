//DragComponent.h

#pragma once

#include "Scene/Components/Component.h"
#include <glm/glm.hpp>
class DragComponent: public Component
{
private:
    bool is_mouse_button = false;
    bool is_mouse_on = false;
    bool hold = false;
    glm::vec2 mpos;
    glm::vec2 offset = glm::vec2(0.0f);
public:
    virtual void Update(float dt);
    virtual void OnEvent  (Event& event);
};