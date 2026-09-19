//Window.h
#pragma once

#include <glad/gl.h>
#include <glfw/glfw3.h>
#include <functional>

#include "Event/Event.h"


class Window
{
private:
    GLFWwindow* window;
    int width;
    int height;
    using EventCallBack = std::function<void(Event&)>;
    EventCallBack eventcallback;
    static void GLFWwindowCloseCallBack(GLFWwindow* window);
    static void GLFWwindowResizeCallBack(GLFWwindow* window,
                                         int width,
                                         int height);
    static void GLFWKeyCallBack(GLFWwindow* window,
                                int key,
                                int scancode,
                                int action,
                                int mod);

    static void GLFWMouseCallBack(GLFWwindow *window,
                                   int button,
                                   int action,
                                   int mods);
    
    static void GLFWCursorPosCallBack(GLFWwindow *window, 
                                      double xpos,
                                      double ypos);
    static void GLFWScrollCallBack(GLFWwindow *window,
                                   double xoffset, 
                                   double yoffset);
public:
    Window(int w, int h, char* name);
    ~Window();

    Window(const Window&)            = delete;
    Window& operator=(const Window&) = delete;

    Window(Window&& other)            noexcept;
    Window& operator=(Window&& other) noexcept;

    bool    windowrunning   ();
    void    clear           ();
    void    SwapBuffer      ();
    void    PollEvents      ();
    GLFWwindow* GetWindow()  {return window;}


    void    WindowResize    (int width, int height);
    int     GetWidth ()  {return width;}
    int     GetHeight()  {return height;}

    void SetEventCallBack(const EventCallBack& callback);
};

