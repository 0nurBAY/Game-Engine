//Input.h

#pragma once

#include "Window/Window.h"

#include <array>
#include <glfw/glfw3.h>

class Input
{
private:
    Window& window;

    std::array<bool, GLFW_KEY_LAST +1> currentKeys  {};
    std::array<bool, GLFW_KEY_LAST +1> previousKeys {};

    std::array<bool, GLFW_MOUSE_BUTTON_LAST +1> currentMouseButtons {};
    std::array<bool, GLFW_MOUSE_BUTTON_LAST +1> previousMouseButtons{};

    double MouseX;
    double MouseY;

    double scrollX = 0.0f;
    double scrollY = 0.0f;

    static void ScrollCallBack(GLFWwindow* window, double XOffset, double YOffset);
public:
    Input(Window& window);

    void Update         ();

    bool IsKeyDown     (int key) const;
    bool IsKeyPressed  (int key) const;
    bool IsKeyReleased (int key) const;

    bool IsMouseButtonDown      (int button) const;
    bool IsMouseButtonPressed   (int button) const;
    bool IsMouseButtonReleased  (int button) const;

    double GetMouseX () const;
    double GetMouseY () const;
    double GetScrollX() const;
    double GetScrollY() const;

};

