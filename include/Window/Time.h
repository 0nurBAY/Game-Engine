//Time.h

#pragma once

#include<glfw/glfw3.h>

class Time
{
private:
    float deltaTime     =0.0f;
    float LastFrameTime =0.0f;
    const float fixedtime;
    bool started = false;
public:
    Time(const float time);
    void    Update      ();
    float   GetDeltaTime() const;
    float   GetFixedDeltaTime() const;
};
