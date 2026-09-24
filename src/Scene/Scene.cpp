//Scene.cpp
#include "Scene/Scene.h"


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
    entitymanager.UpdateEntities(deltatime);
}
void Scene::AnimationUpdate(float deltatime, ResourceManagerPlus *resoursmanager){
    if(!active||destroyed||!inited) return;
    entitymanager.UpdateAnimations(deltatime, resoursmanager);
}
void Scene::OnEvent(Event &event){
    if(!active||destroyed||!inited) return;
    entitymanager.EventEntities(event);
}

EntityManager &Scene::GetEntityManager(){
    return entitymanager;
}
Camera *Scene::GetEntityCamera() const{
    return camera;
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
void Scene::Init(Camera *camera){
    if(inited||destroyed) return;
    inited = true;
    this->camera = camera;
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