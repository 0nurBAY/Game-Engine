//CameraComponent.h

#pragma once
#include "Scene/Components/Component.h"
#include "Renderer/Camera.h"

class CameraComponent : public Component
{
private:
    Camera* camera;
    Entity* target;
public:
    CameraComponent(Camera* camera,Entity* target);

    Entity* GetCameraEntity();
    Entity* GetTarget();
    Camera*  GetCamera();
};

