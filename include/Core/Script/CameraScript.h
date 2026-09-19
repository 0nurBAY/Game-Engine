//CameraScript.h

#pragma once

#include "Core/Script/Script.h"
#include "Renderer/Camera.h"

class CameraScript: public Script
{
private:
    Camera* camera;
    Entity* camera_entity;
    Entity* target;
    

public:
    void Update(float deltatime) override;
    void SetCamera(Camera* camera);
    void SetTarget(Entity* target);
    void SetCameraEntity(Entity* camera_entity);
    void FolowTarget(float deltatime);
};
