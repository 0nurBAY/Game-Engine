//Window.cpp
#include "Window/Window.h"
#include "Event/WindowEvent.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"
#include <iostream>
Window::Window(int w, int h, char* name):width(w),height(h)
{


    if(!glfwInit()) return;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(w,h,name,nullptr,nullptr);

    if(!window){
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    if(!gladLoadGL(glfwGetProcAddress)){
        glfwDestroyWindow(window);
        glfwTerminate();
        window = nullptr;
        return;
    }
    glViewport(0,0,w,h);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glfwSetWindowUserPointer(window, this);
    std::cout << "WINDOW THIS: " << this << "\n";
    std::cout << "GLFW USER POINTER: "
              << glfwGetWindowUserPointer(window) << "\n";
    glfwSetWindowCloseCallback  (window,GLFWwindowCloseCallBack);
    glfwSetWindowSizeCallback   (window,GLFWwindowResizeCallBack);
    glfwSetKeyCallback          (window,GLFWKeyCallBack);
    glfwSetMouseButtonCallback  (window,GLFWMouseCallBack);
    glfwSetCursorPosCallback    (window,GLFWCursorPosCallBack);
    glfwSetScrollCallback       (window,GLFWScrollCallBack);
}

Window::~Window(){
    glfwDestroyWindow(window);
    glfwTerminate();
    window = nullptr;
}

bool Window::windowrunning(){
    return !(glfwWindowShouldClose(window));
}

void Window::clear(){
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::SwapBuffer(){
    glfwSwapBuffers(window);
}

void Window::PollEvents(){
    glfwPollEvents();
}

void Window::WindowResize(int width, int height){
    glfwSetWindowSize(window,width,height);
    this->width = width;
    this->height = height;
    std::cout << "Window W:" << this->width << "\n";
    std::cout << "Window H:" << this->height << "\n";
}






void Window::SetEventCallBack(const EventCallBack &callback){
    eventcallback = callback;
    std::cout << "SET CALLBACK: "
              << (eventcallback ? "DOLU" : "BOS")
              << std::endl;
}


void Window::GLFWwindowCloseCallBack(GLFWwindow *window){
    Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    
     if(!win) {
        std::cout<<"Hata win oluşturulamadı\n";
        return;}
    WindowCloseEvent event;
    if(win->eventcallback)  win->eventcallback(event);
    else std::cout<<"Hata EventCallBack bulunamadı\n";
}
void Window::GLFWwindowResizeCallBack(GLFWwindow *window, int width, int height){
    Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    
    if(!win) {
        std::cout<<"Hata win oluşturulamadı\n";
        return;}

    win->width = width;
    win->height = height;

    WindowResizeEvent event(width,height);
    if(win->eventcallback) win->eventcallback(event);
    else std::cout<<"Hata EventCallBack bulunamadı\n";
}

void Window::GLFWKeyCallBack(GLFWwindow *window, int key, int scancode, int action, int mod){
    Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if(!win) {
        std::cout<<"Hata win oluşturulamadı\n";
        return;}
    if(action == GLFW_PRESS){
        KeyPressedEvent event(key);
        if (win->eventcallback) win->eventcallback(event);
        
    }
    else if (action == GLFW_RELEASE){
        KeyReleasedEvent event(key);
        if(win->eventcallback) win->eventcallback(event);
    }
}
void Window::GLFWMouseCallBack(GLFWwindow *window, int button, int action, int mods){
    Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if(!win) {
        std::cout<<"Hata win oluşturulamadı\n";
        return;}
    if(action == GLFW_PRESS){
        MousePressedEvent event(button);
        if(win->eventcallback) win->eventcallback(event);
    }
    else if(action == GLFW_RELEASE){
        MouseReleasedEvent event(button);
        if(win->eventcallback) win->eventcallback(event);
    }
}
void Window::GLFWCursorPosCallBack(GLFWwindow *window, double xpos, double ypos){
    Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if(!win) {
        std::cout<<"Hata win oluşturulamadı\n";
        return;}
    CursorMoveEvent event(xpos,ypos);
    if(win->eventcallback) win->eventcallback(event);

}
void Window::GLFWScrollCallBack(GLFWwindow *window, double xoffset, double yoffset){
    Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if(!win) {
        std::cout<<"Hata win oluşturulamadı\n";
        return;}
    ScrollEvent event(xoffset,yoffset);
    if(win->eventcallback) win->eventcallback(event);

}