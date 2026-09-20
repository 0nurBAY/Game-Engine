//Engine.cpp
#include "Engine/Engine.h"
#include "Scene/Entity.h"
#include "Resource/Assetloader.h"

#include <iostream>
#include <fstream>
#include <sstream>


std::string ReadShader(const std::string &path){
    std::ifstream file(path);
    if(!file.is_open()){ std::cout<<"!FILE "<<path<<" couldn't open\n"; return "";}
    std::stringstream shader;
    shader << file.rdbuf();

    file.close();
    return shader.str();
}

void Engine::ReadResources(const std::string &path){
    std::ifstream file(path);
    if(!file.is_open()){ std::cout<<"!FILE "<<path<<" couldn't open\n"; return;}
    std::string line;
    while (std::getline(file,line)){
        if(line.empty() || line[0]=='#') continue;
        std::stringstream ss(line);
        ParsedResource resource;
        ss >> resource.type;
        ss >> resource.name;
        std::string args;
        while(ss >> args){
            resource.args.push_back(args);
        }
        printf("TYPE: %s\nNAME: %s\n",resource.type.c_str(),resource.name.c_str());
        for(auto& arg:resource.args){
            printf("ARG: %s\n",arg.c_str());
        }
        printf("\n");
    }
    file.close();
}
void Engine::IncludeAsset(const std::string &type, const std::string &name, const std::vector<std::string> &args){
    resoursmanager.IncludeItem<Texture>(name,args[0].c_str());
}
void Engine::ReadScenes(const std::string &path){
    std::ifstream file(path);
    if(!file.is_open()){ std::cout<<"!FILE "<<path<<" couldn't open\n"; return;}
    std::string line;
    while (std::getline(file,line)){

    }
    file.close();
}

Engine::Engine():
window(1200,1200,"Pencere"),
input(window),
camera(window.GetWidth(),window.GetHeight()),
renderer(camera,window.GetWidth(),window.GetHeight(),ReadShader("shaders/deneme.vert").c_str(),ReadShader("shaders/deneme.frag").c_str())
{
}

void Engine::Init(){
    std::cout <<"CCCCCCCCCCCCCCCCCCCCC\n";
    camera.SetPosition(glm::vec3(0.0f,0.0f,0.0f));
    camera.SetWorldSize(100000.0f, 100000.0f, 50000.0f, -50000.0f, 50000.0f, -50000.0f);
    window.SetEventCallBack([this](Event& event){
        OnEvent(event);
    });
    ReadResources("resources/resources.res");

}

void Engine::PushScene(std::unique_ptr<Scene> scene){
    scenestack.push_back(std::move(scene));
    scenestack.back()->Init();
    scenestack.back()->Activate();
}

void Engine::PopScene(){
    
    if(!scenestack.empty()){ 
        scenestack.back()->Exit();
        scenestack.back()->Destroy();
        scenestack.pop_back();}
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
    
    time.Update();
    input.Update();
    window.clear();
    camera.Update(time.GetDeltaTime());
    if(currentscene){
    currentscene->Update(time.GetDeltaTime());
    currentscene->AnimationUpdate(time.GetDeltaTime(),&resoursmanager);
    }

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
    renderer.Draw(*currentscene, resoursmanager);
    ////
}

void Engine::OnEvent(Event& event){
    EventDispatcher dispatcher(event);

    Scene* currentscene = GetActiveScene();
    if(currentscene){
        currentscene->OnEvent(event);
    }
    dispatcher.Dispatcher<WindowCloseEvent>(
        [this](WindowCloseEvent& event){
            Stop();
        }
    );
    dispatcher.Dispatcher<WindowResizeEvent>(
        [this](WindowResizeEvent& event)
        {
            int w =event.GetWidth();
            int h =event.GetHeight();
            // std::cout << "Resize: " <<w <<","<<h <<"\n";
            glViewport(0,0,w,h);
            this->renderer.SetProjection(w,h);
            this->window.WindowResize(w,h);
        }
    );
    dispatcher.Dispatcher<KeyPressedEvent>(
        [this](KeyPressedEvent& event)
        {
            // std::cout << "Key pressed: "<<event.GetKey() <<"\n";
            if(event.GetKey()==GLFW_KEY_O){
                this->camera.Shake(15.0f,0.2f);
            }
            if(event.GetKey()==GLFW_KEY_K){
                this->camera.Shake(20.0f,0.2f);
            }
            if(event.GetKey()==GLFW_KEY_L){
                this->camera.Shake(30.0f,0.2f);
            }
        }
    );
    dispatcher.Dispatcher<MousePressedEvent>(
        [](MousePressedEvent& event)
        {
            // std::cout << "Key pressed: "<<event.GetButton() <<"\n";
        }
    );
    dispatcher.Dispatcher<CursorMoveEvent>(
        [](CursorMoveEvent& event)
        {}
    );
    dispatcher.Dispatcher<ScrollEvent>(
        [](ScrollEvent& event)
        {
            // std::cout << "Scroll Offsets: "<<event.GetXOffset() <<","<<event.GetYOffset() <<"\n";
        }
    );

}