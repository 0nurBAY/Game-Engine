//Scene.h
#pragma once
#include "Scene/EntityManager.h"
#include <string>
#include "Renderer/Camera.h"

class Scene
{
private:
    Camera* camera;
    EntityManager entitymanager;
    const std::string name;   
    bool active    = false;
    bool inited    = false;
    bool destroyed = false;
    
protected:
    virtual void OnCreate   () {};
    virtual void OnExit     () {};
    virtual void OnDestroy  () {};
    virtual void OnActive   () {};
public:
    uint64_t    AddEntity(std::string name);
    void        DeleteEntity(uint64_t id);
    Entity*     FindEntity(uint64_t id);
    EntityManager& GetEntityManager();
    Camera* GetEntityCamera () const;

    void Update (float deltatime);
    void AnimationUpdate (float deltatime,ResourceManagerPlus* resoursmanager);
    void OnEvent (Event& event);
    void Activate();
    void Exit    ();
    void Init    (Camera* camera);
    void Destroy ();

    std::string Name() const;
    Scene           (std::string name);
};
