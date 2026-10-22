//Engine.cpp
#include "Engine/Engine.h"
#include "Scene/Entity.h"
#include "Core/Assetloader.h"
#include "Core/Sceneloader.h"
#include "Core/ScriptManager.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <Windows.h>
std::string ReadShader(const std::string &path);

void Engine::ReadResourcesFile(const std::string &path){
    const std::filesystem::path directory{path};
    for(const auto& files: std::filesystem::directory_iterator(directory)){
        std::ifstream file(files.path());
        if(!file.is_open()){ std::cout<<"!FILE "<<files.path()<<" couldn't open\n"; return;}
        std::string line;
        bool scene = false;
        if(files.path().extension()==".lvl") scene = true;
        else if(files.path().extension()==".res") scene = false;
        else continue;
        AssetLoader assetloader;
        SceneLoader sceneloader;
        assetloader.Init();
        sceneloader.Init();
        
        while (std::getline(file,line)){
            if(line.empty() || line[0]=='#') {
                if(scene) sceneloader.LineCounter();
                else assetloader.LineCounter();
                continue;
            }
            std::stringstream ss(line);
            ParsedResource resource;
            resource.file = files.path().string();
            ss >> resource.type;
            ss >> resource.name;
            std::string args;
            while(ss >> args){
                resource.args.push_back(args);
            }
            try{
            if(scene) sceneloader.LoadScene(resource,assets,scriptmanager,&input,camera);
            else assetloader.LoadAsset(resource,resoursmanager,assets);
            }
            catch(const std::exception& e){
                std::cerr << "Exception: " << e.what() << "\n";
                MessageBoxA(nullptr,e.what(),"Load Error",MB_OK|MB_ICONERROR);
                std::exit(EXIT_FAILURE);
            }
        }
        if(scene) PushScene(sceneloader.GetScene());
        file.close();
    }
}

Engine::Engine():
window(1200,600,"Pencere"),
input(window),
camera(window.GetWidth(),window.GetHeight()),
renderer(camera,window.GetWidth(),window.GetHeight(),ReadShader("shaders/deneme.vert").c_str(),ReadShader("shaders/deneme.frag").c_str()),
time(1.0f/60.0f),
debugrenderer(ReadShader("shaders/solidcolor.vert").c_str(),ReadShader("shaders/solidcolor.frag").c_str())
{
}

void Engine::Init(){
    scriptmanager.Init();
    fixed_dt = time.GetFixedDeltaTime();
    camera.SetPosition(glm::vec3(0.0f,0.0f,0.0f));
    camera.SetWorldSize(100000.0f, 100000.0f, 50000.0f, -50000.0f, 50000.0f, -50000.0f);
    window.SetEventCallBack([this](Event& event){
        OnEvent(event);
    });
    ReadResourcesFile("resources");

    Scene* currentscene = GetActiveScene();
    physics.Init(fixed_dt,currentscene);
    // ReadResources("resources/resources.res");
    // ReadScenes("resources/scene1.lvl");
}

void Engine::PushScene(std::unique_ptr<Scene> scene){
    scenestack.push_back(std::move(scene));
    scenestack.back()->Init(&camera,this);
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
    running = true;
    Init();
    GameLoop();
}
void Engine::Stop(){
    running = false;
}

void Engine::Update(){
    sw.reset();
    //Daha sonra her Scene'i döndürür ve hepsine update verir ve hepsi kendi içinde aktif olan kısımlarını döndürür
    Scene* currentscene = GetActiveScene();
    time.Update();
    debugrenderer.BeginFrame();
    float dt = time.GetDeltaTime();
    input.Update();
    window.clear();
    camera.Update(dt);
    double Gaged_Update = sw.Ms();
    // if(!Prevp && input.IsKeyPressed(GLFW_KEY_P))pause = !pause;
    // Prevp = input.IsKeyPressed(GLFW_KEY_P);
    // Prevo = input.IsKeyPressed(GLFW_KEY_O);
    double Component_Update;
    double Animation_Update;
    if(!pause || step){
        if(currentscene){
            currentscene->Update(dt);
            Component_Update = sw.Ms();
            physics.FixedUpdate(dt);
            // auto physicRes = physics.GetCollisions();
            // for(auto& res: physicRes){
                // if(!res.collision) return;
                // std::cout << "======================================\n";
                // debugrenderer.DrawPoint(res.contact1,glm::vec4(1.0f,0.0,0.0f,1.0f));
                // debugrenderer.DrawPoint(res.contact2,glm::vec4(0.0f,1.0,0.0f,1.0f));
                // float cosA = glm::cos(glm::radians(res.rot1));
                // float sinA = glm::sin(glm::radians(res.rot1));
                // float cosB = glm::cos(glm::radians(res.rot2));
                // float sinB = glm::sin(glm::radians(res.rot2));
                // glm::vec2 CoordinatesA[4] ={
                //     res.center1+glm::vec2(res.halfextend1.x*cosA-res.halfextend1.y*sinA,res.halfextend1.y*cosA+res.halfextend1.x*sinA),
                //     res.center1+glm::vec2(-res.halfextend1.x*cosA-res.halfextend1.y*sinA,res.halfextend1.y*cosA-res.halfextend1.x*sinA),
                //     res.center1+glm::vec2(-res.halfextend1.x*cosA+res.halfextend1.y*sinA,-res.halfextend1.y*cosA-res.halfextend1.x*sinA),
                //     res.center1+glm::vec2(res.halfextend1.x*cosA+res.halfextend1.y*sinA,-res.halfextend1.y*cosA+res.halfextend1.x*sinA)
                // };
                // glm::vec2 CoordinatesB[4] ={
                //     res.center2+glm::vec2(res.halfextend2.x*cosB-res.halfextend2.y*sinB,res.halfextend2.y*cosB+res.halfextend2.x*sinB),
                //     res.center2+glm::vec2(-res.halfextend2.x*cosB-res.halfextend2.y*sinB,res.halfextend2.y*cosB-res.halfextend2.x*sinB),
                //     res.center2+glm::vec2(-res.halfextend2.x*cosB+res.halfextend2.y*sinB,-res.halfextend2.y*cosB-res.halfextend2.x*sinB),
                //     res.center2+glm::vec2(res.halfextend2.x*cosB+res.halfextend2.y*sinB,-res.halfextend2.y*cosB+res.halfextend2.x*sinB)
                // };
                // for(int i=0; i<4; i++){
                //     if(i<3){
                //     debugrenderer.DrawLine(CoordinatesB[i],CoordinatesB[i+1],glm::vec4(0.3f,0.8,0.8f,1.0f));
                //     continue;
                //     }
                //     debugrenderer.DrawLine(CoordinatesB[i],CoordinatesB[0],glm::vec4(0.3f,0.8,0.8f,1.0f));
                // }
                // debugrenderer.DrawCircle(res.center1,res.radius1,glm::vec4(0.0f,0.0f,1.0f,1.0f));
                // debugrenderer.DrawBox(glm::vec2(-res.halfextend1.x,-res.halfextend1.y)+res.center1,glm::vec2(res.halfextend1.x,res.halfextend1.y)+res.center1,glm::vec4(0.0f,1.0f,1.0f,1.0f));
                // debugrenderer.DrawBox(glm::vec2(-res.halfextend2.x,-res.halfextend2.y)+res.center2,glm::vec2(res.halfextend2.x,res.halfextend2.y)+res.center2,glm::vec4(0.0f,1.0f,1.0f,1.0f));
                // debugrenderer.DrawPoint((glm::distance(res.center1,res.center2)/(res.radius1+res.radius2)*(res.radius1))*res.normal+res.center1,glm::vec4(0.3f,0.8,0.8f,1.0f));
                // debugrenderer.DrawLine(res.center1,res.center1+res.normal*res.halfextend1,glm::vec4(1.0f,0.0,0.0f,1.0f));
                // debugrenderer.DrawLine(res.center2,res.center2-res.normal*res.halfextend2,glm::vec4(0.0f,1.0,0.0f,1.0f));
                // debugrenderer.DrawLine(res.center1,res.center1 + res.normal * res.penetration,glm::vec4(1.0f));
                // if(res.contacts.size() == 1) debugrenderer.DrawPoint(res.contacts[0],glm::vec4(1.0f));
                // if(res.contacts.size() > 1){
                //     for(int k = 0; k < res.contacts.size()-1;k++){
                //         debugrenderer.DrawLine(res.contacts[k],res.contacts[k+1],glm::vec4(1.0f,0.0,0.0f,1.0f));
                //         debugrenderer.DrawPoint(res.contacts[k],glm::vec4(1.0f));
                //         debugrenderer.DrawPoint(res.contacts[k+1],glm::vec4(1.0f));
                //     }
                // }
            // }
            currentscene->AnimationUpdate(dt,&resoursmanager);
            Animation_Update = sw.Ms();
        }
    }
    debugrenderer.DrawBox(glm::vec2(camera.GetPosition().x-50.0f,camera.GetPosition().y-50.f),glm::vec2(camera.GetPosition().x+50.0f,camera.GetPosition().y+50.f), glm::vec4(1,0,0,1));
    step = false;
    std::cout << "FPS: " << 1/dt << "\n";

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
    
    float cam_widht  = camera.GetWidth() *0.5f*camera.GetZoom() - 200.0f;
    float cam_height = camera.GetHeight()*0.5f*camera.GetZoom() - 200.0f;
    debugrenderer.DrawBox(glm::vec2(camera.GetPosition().x - cam_widht,camera.GetPosition().y - cam_height),glm::vec2(camera.GetPosition().x + cam_widht,camera.GetPosition().y + cam_height),glm::vec4(0.7f,0.7f,0.2f,1.0f));
    
    debugrenderer.Flush(camera.GetProjectionMatrix(),camera.GetViewMatrix());

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
            if(event.GetKey()==GLFW_KEY_P){
                pause = !pause;
            }
            if(event.GetKey()==GLFW_KEY_O){
                step = true;
            }
            // if(event.GetKey()==GLFW_KEY_K){
            //     this->camera.Shake(20.0f,0.2f);
            // }
            // if(event.GetKey()==GLFW_KEY_L){
            //     this->camera.Shake(30.0f,0.2f);
            // }
        }
    );
    dispatcher.Dispatcher<MousePressedEvent>(
        [this](MousePressedEvent& event)
        {}
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