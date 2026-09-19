//PlayerScript.h

#pragma once

#include "Core/Script/Script.h"
#include <glm/glm.hpp>

class PlayerScript: public Script
{
private:
    glm::vec2 lastdirection = glm::vec2(0.0f,-1.0f);
public:
    void Update(float deltatime) override;
};
