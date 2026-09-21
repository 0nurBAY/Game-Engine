//CameraComponent.cpp
#include "Scene/Components/CameraComponent.h"

CameraComponent::CameraComponent(Camera *camera, Entity *target):
camera(camera),
target(target){}

Entity *CameraComponent::GetCameraEntity(){return owner;}
Entity *CameraComponent::GetTarget()      {return target;}
Camera *CameraComponent::GetCamera()      {return camera;}