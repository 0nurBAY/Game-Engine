//CameraScript.cpp

#include "Core/Script/CameraScript.h"
#include "Scene/Entity.h"
#include "Core/Input.h"
#include <iostream>
#include <glfw/glfw3.h>
#include <iostream>

void CameraScript::OnCreate(){
    camera        = entity->GetComponent<CameraComponent>()->GetCamera();
    std::cout << "CameraScript::OnCreate: Camera pointer: " << camera << "\n";
    target        = entity->GetComponent<CameraComponent>()->GetTarget();
    std::cout << "CameraScript::OnCreate: Target pointer: " << target << "\n";
    camera_entity = entity->GetComponent<CameraComponent>()->GetCameraEntity();
    std::cout << "CameraScript::OnCreate: Camera Entity pointer: " << camera_entity << "\n";
}
void CameraScript::Update(float deltatime){
    if (!camera||!target||!camera_entity) return;
    auto* i   = GetInput(); 
    FolowTarget(deltatime);

    if(i->IsKeyDown(GLFW_KEY_Q)) {
        std::cout << "Geted: " <<camera->GetZoom() <<"\n";
        // std::cout << "Value: " <<camera->GetZoom()*0.8f*deltatime <<"\n";
        camera->SetZoom(camera->GetZoom()*0.8f);
        // std::cout << "Seted: " <<camera->GetZoom() <<"\n";
    }
    if(i->IsKeyDown(GLFW_KEY_E)) {
        std::cout << "Geted: " <<camera->GetZoom() <<"\n";
        // std::cout << "Value: " <<camera->GetZoom()*1.2f <<"\n";
        camera->SetZoom(camera->GetZoom()*1.2f);
        // std::cout << "Seted: " <<camera->GetZoom() <<"\n";
    }
    
}
void CameraScript::SetCamera(Camera *camera){
    this->camera = camera;
}
void CameraScript::SetTarget(Entity *target){
    this->target = target;
}
void CameraScript::SetCameraEntity(Entity *camera_entity){
    this->camera_entity = camera_entity;
}
void CameraScript::FolowTarget(float deltatime){
    float speed = 5.0f;
    auto targetPos = target->GetComponent<TransformComp>()->position;
    auto cameraPos =  camera->GetPosition();
    float smoothness = 1.0f - std::exp(-speed * deltatime);

    glm::vec2 newPos = glm::mix(
        glm::vec2(cameraPos.x, cameraPos.y),
        targetPos,
        smoothness
    );
    
    camera->SetPosition(glm::vec3(newPos, cameraPos.z));
}
