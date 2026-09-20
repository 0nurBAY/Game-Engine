//Engine.h
#pragma once

#include "Scene/Scene.h"
#include "Window/Window.h"
#include "Renderer/Renderer.h"
#include "Renderer/Camera.h"
#include "Resource/ResourceManagerPlus.h"
#include "Resource/AssetHandleBase.h"
#include "Core/Input.h"
#include "Event/Events.h"
#include "Window/Time.h"
#include <memory>
#include <vector>
#include <unordered_map>

class Engine
{
private:
    std::vector<std::unique_ptr<Scene>> scenestack;
    Window window;
    Input input;
    Camera camera;
    Renderer renderer;
    //Audio
    //Assets
    Time time;
    ResourceManagerPlus resoursmanager;
    std::unordered_map<std::string,std::unique_ptr<AssetHandleBase>> assets;
    bool running;
    void Update();
    void Render();
    void Init();
    void OnEvent(Event& event);
    // void Physics();
    // void Shutdown();
    void GameLoop();
    void ReadResources(const std::string &path);
    void ReadScenes(const std::string &path);
    
public:
    Engine();

    void PushScene(std::unique_ptr<Scene> scene);
    void PopScene();
    Scene* GetActiveScene() const;
    

    void Run();
    void Stop();

};

