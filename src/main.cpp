//main.cpp
#include "Renderer/Renderer.h"
#include "Window/Window.h"
#include "Window/Time.h"
#include "Core/Input.h"
#include "Event/EventDispatcher.h"
#include "Event/WindowEvent.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"
#include "Resource/ResourceManagerPlus.h"
#include "Core/Script/TestScript.h"
#include "Core/Script/PlayerScript.h"
#include "Core/Script/CameraScript.h"
#include "Core/Script/HandsScript.h"
#include "Core/Script/TestScript2.h"
#include "Core/Animation.h"
#include "Engine/Engine.h"

#include <iostream>
#include <iomanip>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <fstream>
#include <sstream>

int main(){
    Engine engine;

    engine.Run();

    return 0;
}