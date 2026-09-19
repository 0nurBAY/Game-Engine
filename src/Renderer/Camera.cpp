//Camera.cpp

#include "Renderer/Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <iostream>
Camera::Camera(float width, float height): 
    Baseposition(0.0f,0.0f,0.0f),
    rotation(0.0f),
    zoom(1.0f),
    width(width),
    height(height),
    resW(width),
    resH(height)
{
}

void Camera::Update(float dt){
    if(shakeDuration<=0){
        shakeDuration = 0.0f;
    }else{
        float shakex = perlin.octave2D((glfwGetTime()*frequency),(0),4);
        float shakey = perlin.octave2D((0),(glfwGetTime()*frequency),4);
        shakeOffset = glm::vec3(shakex,shakey,0.0f) * shakeMagnnitude * (shakeDuration/shakeTime);
        shakeDuration-=dt;
    }

    position = Baseposition + shakeOffset;
}


void Camera::SetPosition(const glm::vec3 &new_position){

    float realwidth = width*zoom;
    float realheight = height*zoom;
    float maxX = worldRight - realwidth/2;
    float minX = worldLeft  + realwidth/2;

    float maxY = worldTop       - realheight /2;
    float minY = worldBottom    + realheight /2;

    Baseposition = new_position;

    if(realwidth > worldRight - worldLeft) {Baseposition.x = (worldRight - worldLeft)/2;}
    else Baseposition.x = std::clamp(Baseposition.x,minX,maxX);
    
    if(realheight > worldTop - worldBottom) {Baseposition.y = (worldTop - worldBottom)/2;}
    else Baseposition.y = std::clamp(Baseposition.y,minY,maxY);
    
}
void Camera::SetRotation(const float &new_rotation){
    rotation = new_rotation;
}
void Camera::SetZoom(const float &new_zoom){
    zoom = new_zoom;
}
void Camera::SetSize(float width, float height,float w,float h){
    this->width  = width;
    this->height = height;
    this->resH = h;
    this->resW = w;
}

void Camera::SetWorldSize(float width, float height, float r, float l, float t, float b){
    this->worldWidth  = width;
    this->worldHeight = height;

    this->worldRight  = r;
    this->worldLeft   = l;
    this->worldTop    = t;
    this->worldBottom = b;
}
float Camera::GetWidth() const{
    return width;
}
float Camera::GetHeight() const{
    return height;
}

float Camera::GetWorldWidthAspect(){
    return (width/resW)* zoom;
}
float Camera::GetWorldHeightAspect(){
    return (height/resH)* zoom;
}

glm::vec3 Camera::GetPosition() const{
    return position;
}
float Camera::GetRotation() const{
    return rotation;
}
float Camera::GetZoom() const{
    return zoom;
}
float Camera::GetResW() const{
    return resW;
}
float Camera::GetResH() const{
    return resH;
}
glm::vec2 Camera::ScreentoWorld(float ScreenX, float ScreenY){
    glm::vec2 asp = glm::vec2(GetWorldWidthAspect(),GetWorldHeightAspect());
    glm::vec2 pos = glm::vec2(ScreenX-resW * 0.5f,resH * 0.5f -ScreenY);
    pos *= asp;
    pos+=glm::vec2(position.x,position.y);
    return pos;
}

glm::vec2 Camera::WorldToScreen(float WindowX,float WindowY){
    glm::vec2 pos = glm::vec2(WindowX-position.x,WindowY-position.y);  
    glm::vec2 asp = glm::vec2(GetWorldWidthAspect(),GetWorldHeightAspect());
    pos /= asp;
    

    pos.x = resW * 0.5f + pos.x;
    pos.y = resH * 0.5f - pos.y;

    return pos;
}

void Camera::Shake(float strength, float duration){
    shakeMagnnitude = strength;
    shakeDuration = duration;
    shakeTime = duration;
}

glm::mat4 Camera::GetViewMatrix() const{
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(
        view,
        -position
    );
    view = glm::rotate(
        view,
        glm::radians(-rotation),
        glm::vec3(0.0f,0.0f,1.0f)
    );
    return view;
}
glm::mat4 Camera::GetProjectionMatrix() const{
    return glm::ortho(
        -(width * zoom)*0.5f,(width * zoom)*0.5f,
        -(height * zoom)*0.5f,(height * zoom)*0.5f
    );
}