//Engine.h
#pragma once

#include "Scene/Scene.h"
#include "Window/Window.h"
#include "Renderer/Renderer.h"
#include "Renderer/Camera.h"
#include "Core/Input.h"
#include "Event/Events.h"
#include "Window/Time.h"
#include <memory>
#include <vector>

class Engine
{
private:
    std::vector<std::unique_ptr<Scene>> scenestack;
    Window window;
    Input input;
    Renderer renderer;
    Camera camera;
    //Audio
    //Assets
    Time time;
    bool running;
    void Update();
    void Render();
    void Init();
    void OnEvent(Event& event);
    // void Physics();
    // void Shutdown();
    void GameLoop();
public:
    Engine();

    void PushScene(std::unique_ptr<Scene> scene);
    void PopScene();
    Scene* GetActiveScene() const;
    
    

    void Run();
    void Stop();

};

