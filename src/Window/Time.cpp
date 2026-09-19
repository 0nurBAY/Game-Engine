//Time.cpp
#include "Window/Time.h"

void Time::Update(){
    LastFrameTime = deltaTime;
    deltaTime = glfwGetTime();
}
float Time::GetDeltaTime(){
    return (deltaTime-LastFrameTime);
}