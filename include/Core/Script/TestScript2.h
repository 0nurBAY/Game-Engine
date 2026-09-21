//TestScript2.h

#pragma once
#include "Core/Script/Script.h"
#include <glm/glm.hpp>
#include <random>
class TestScript2 :public Script
{
private:
    bool arrived = true;
    float walktime;
    float walked =0.0f;
    glm::vec2 goal;
    glm::vec2 lastdirection;
    float delay=5.0f;
    float timepased=0.0f;

public:
    void Update(float deltatime) override;
    void Decide(float deltatime);
};
