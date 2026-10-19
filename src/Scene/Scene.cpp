//Scene.cpp
#include "Scene/Scene.h"
#include "Engine/Engine.h"

Scene::Scene(std::string name):name(name){}

std::string Scene::Name() const{
    return name;
}

uint64_t Scene::AddEntity(std::string name){
    return entitymanager.CreateEntity(name);
}
void Scene::DeleteEntity(uint64_t id){
    entitymanager.DestroyEntity(id);
}
Entity* Scene::FindEntity(uint64_t id){
    return entitymanager.FindEntity(id);
}

void Scene::Update(float deltatime){
    if(!active||destroyed||!inited) return;
    float cam_x = camera->GetPosition().x;
    float cam_y = camera->GetPosition().y;
    float r = std::max(cam_x,cam_y)*camera->GetZoom() + 200.f;
    entitymanager.UpdateEntities(deltatime,cam_x,cam_y,r);
}
void Scene::AnimationUpdate(float deltatime, ResourceManagerPlus *resoursmanager){
    if(!active||destroyed||!inited) return;
    float cam_x = camera->GetPosition().x;
    float cam_y = camera->GetPosition().y;
    float r = std::max(cam_x,cam_y)*camera->GetZoom()+ 50.0f;
    entitymanager.UpdateAnimations(deltatime,cam_x,cam_y,r, resoursmanager);
}
void Scene::OnEvent(Event &event){
    if(!active||destroyed||!inited) return;
    float cam_x = camera->GetPosition().x;
    float cam_y = camera->GetPosition().y;
    float r = std::max(cam_x,cam_y)*camera->GetZoom() + 200.f;
    entitymanager.EventEntities(event,cam_x,cam_y,r);
}

EntityManager &Scene::GetEntityManager(){
    return entitymanager;
}
Camera *Scene::GetEntityCamera() const{
    return camera;
}
DebugRenderer *Scene::GetDebugRenderer() const{
    return engine->GetDebugRenderer();
}
void Scene::Activate(){
    if(active||destroyed) return;
    active = true;
    OnActive();
}
void Scene::Exit(){
    if(!active||destroyed) return;
    active = false;
    OnExit();
}
void Scene::Init(Camera *camera,Engine* engine){
    if(inited||destroyed) return;
    inited = true;
    this->camera = camera;
    this->engine = engine;
    for(auto&[id,entity]:entitymanager.GetEntites()){
        entity->init(this);
    }
    OnCreate();
}
void Scene::Destroy(){
    if(destroyed) return;
    destroyed = true;
    for(auto&[id,entity]:entitymanager.GetEntites()){
        entity->OnDestroy();
    }
    OnDestroy();
}