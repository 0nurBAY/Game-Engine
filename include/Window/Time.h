//Time.h

#pragma once

#include<glfw/glfw3.h>

class Time
{
private:
    float deltaTime     =0.0f;
    float LastFrameTime =0.0f;
public:
    void    Update      ();
    float   GetDeltaTime();
};
