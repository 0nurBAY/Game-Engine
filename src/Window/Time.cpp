//Time.cpp
#include "Window/Time.h"

Time::Time(float time):fixedtime(time){}
void Time::Update(){
    if(!started){
        deltaTime = glfwGetTime(); 
        started = true; 
        return;
    }
    LastFrameTime = deltaTime;
    deltaTime = glfwGetTime();
}
float Time::GetDeltaTime() const{
    return (deltaTime-LastFrameTime);
}

float Time::GetFixedDeltaTime() const{
    return fixedtime;
}