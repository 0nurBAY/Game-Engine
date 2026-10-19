//Engine.h
#pragma once

#include "Scene/Scene.h"
#include "Window/Window.h"
#include "Renderer/Renderer.h"
#include "Renderer/Camera.h"
#include "Resource/ResourceManagerPlus.h"
#include "Resource/AssetHandleBase.h"
#include "Core/ScriptManager.h"
#include "Core/Input.h"
#include "Event/Events.h"
#include "Window/Time.h"
#include "Physics/PhysicSystem.h"
#include "Renderer/DebugRenderer.h"
#include "Core/Stopwatch.h"

#include <memory>
#include <vector>
#include <unordered_map>

class Engine
{
private:
    bool pause = false, step = false;
    std::vector<std::unique_ptr<Scene>> scenestack;
    Window window;
    Input input;
    Camera camera;
    Renderer renderer;
    DebugRenderer debugrenderer;
    ScriptManager scriptmanager;
    Stopwatch sw;
    //Audio
    Time time;
    float fixed_dt=0;
    ResourceManagerPlus resoursmanager;
    PhysicSystem physics;
    std::unordered_map<std::string,std::unique_ptr<AssetHandleBase>> assets;
    bool running;
    void Update();
    void Render();
    void Init();
    void OnEvent(Event& event);
    // void Shutdown();
    void GameLoop();
    void ReadResourcesFile(const std::string &path);
    void ReadResources(const std::string &path);
    void ReadScenes(const std::string &path);
    
public:
    Engine();

    void PushScene(std::unique_ptr<Scene> scene);
    void PopScene();
    Scene* GetActiveScene() const;
    

    void Run();
    void Stop();

    DebugRenderer* GetDebugRenderer() {return &debugrenderer;}
};

