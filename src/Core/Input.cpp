//Input.cpp

#include "Core/Input.h"

Input::Input(Window& window): window(window){
    
    // glfwSetScrollCallback(window.GetWindow(),ScrollCallBack);

}

void Input::Update(){
    previousKeys = currentKeys;

    for (int key=0; key<=GLFW_KEY_LAST; ++key){
        currentKeys[key] = glfwGetKey(window.GetWindow(),key) == GLFW_PRESS;
    }


    previousMouseButtons = currentMouseButtons;
    for (int key=0; key<=GLFW_MOUSE_BUTTON_LAST; ++key){
        currentMouseButtons[key] = glfwGetMouseButton(window.GetWindow(),key) == GLFW_PRESS;
    }

    glfwGetCursorPos(window.GetWindow(),&MouseX,&MouseY);
}

bool Input::IsKeyDown(int key) const{
    return currentKeys[key];
}
bool Input::IsKeyPressed(int key) const{
    return currentKeys[key] && !previousKeys[key];
}
bool Input::IsKeyReleased(int key) const{
    return !currentKeys[key] && previousKeys[key];

}


bool Input::IsMouseButtonDown(int button) const{
    return currentMouseButtons[button];
}
bool Input::IsMouseButtonPressed(int button) const{
    return currentMouseButtons[button] && !previousMouseButtons[button];

}
bool Input::IsMouseButtonReleased(int button) const{
    return !currentMouseButtons[button] && previousMouseButtons[button];

}


double Input::GetMouseX() const{
    return MouseX;
}
double Input::GetMouseY() const{
    return MouseY;
}
double Input::GetScrollX() const{
    return scrollX;
}
double Input::GetScrollY() const{
    return scrollY;
}
void Input::ScrollCallBack(GLFWwindow *window, double XOffset, double YOffset){

    Input* input =static_cast<Input*>(glfwGetWindowUserPointer(window));
    input->scrollX = XOffset;
    input->scrollY = YOffset;
}