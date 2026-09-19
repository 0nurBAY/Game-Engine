//Engine.cpp
#include "Engine/Engine.h"
#include "Scene/Entity.h"
#include <iostream>

Engine::Engine():
window(1200,1200,"Pencere"),
input(window),
renderer(
        R"(
    #version 330 core

    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec2 aTexCoord;

    out vec2 TexCoord;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;
    void main()
    {
        gl_Position = projection * view * model * vec4(aPos, 1.0);
        TexCoord = aTexCoord;
    }
    )",

        R"(
    #version 330 core

    in vec2 TexCoord;
    out vec4 FragColor;

    uniform sampler2D ourTexture;
    uniform bool      useTexture;
    uniform vec4      solidColor;
    void main()
    {
        if(useTexture){
            FragColor = texture(ourTexture,TexCoord);
        }else{
            FragColor = solidColor;
        }
    }
    )")
{
}

void Engine::Init(){
    std::cout <<"CCCCCCCCCCCCCCCCCCCCC\n";
    camera.SetPosition(glm::vec3(0.0f,0.0f,0.0f));
    window.SetEventCallBack([this](Event& event){
        OnEvent(event);
    });

}

void Engine::PushScene(std::unique_ptr<Scene> scene){
    scenestack.push_back(std::move(scene));
}

void Engine::PopScene(){
    
    if(scenestack.size()>0) scenestack.pop_back();
}

Scene* Engine::GetActiveScene() const{

    if(scenestack.empty()) return nullptr;
    return scenestack.back().get();

}

void Engine::Run(){
    std::cout <<"BBBBBBBBBBBBBBBB\n";
    running = true;
    Init();
    GameLoop();
}
void Engine::Stop(){
    running = false;
}

void Engine::Update(){
    //Daha sonra her Scene'i döndürür ve hepsine update verir ve hepsi kendi içinde aktif olan kısımlarını döndürür
    Scene* currentscene = GetActiveScene();
    // if(currentscene)currentscene->Update();
    time.Update();
    input.Update();
    window.clear();
    

}
void Engine::GameLoop(){

    while(running){
        Update();
        Render();
        window.SwapBuffer();
        window.PollEvents();
    }
}

void Engine::Render(){
    Scene* currentscene = GetActiveScene();
    if(!currentscene) return;
    renderer.Draw(*currentscene,camera);
    ////
}

void Engine::OnEvent(Event& event){
    EventDispatcher dispatcher(event);

    dispatcher.Dispatcher<WindowCloseEvent>(
        [this](WindowCloseEvent& event){
            Stop();
        }
    );

    dispatcher.Dispatcher<WindowResizeEvent>(
        [this](WindowResizeEvent& event){
            int w =event.GetWidth();
            int h =event.GetHeight();
            // window.WindowResize(event.GetWidth(),event.GetHeight());
            glViewport(0,0,w,h);
            renderer.SetProjection(w,h);
        }
    );

}