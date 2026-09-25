//AnimationComponent.h
#pragma once 

#include "Scene/Components/Component.h"
#include "Core/Animation.h"
#include "Resource/AssetHandle.h"
#include <glm/glm.hpp>
#include <unordered_map>
class AnimationComponent: public Component
{
private:
    std::unordered_map<std::string,AssetHandle<Animation>> animations;
    std::string current_animation;
    std::string request;
    bool reset = 0;
    glm::vec2 direction =glm::vec2(0.0f,-1.0f);
public:
    AnimationComponent();
    void AddAnimation(const std::string name, const AssetHandle<Animation>& animation);
    void AnimationUpdate(float dt,ResourceManagerPlus* resourceManager) override;
    void OnEvent(Event& event) override;
    void RequestAnimation(const std::string& name);
    void Play(ResourceManagerPlus* resourceManager);
    void Reset();
    void SetDirection(glm::vec2 dir);
    std::shared_ptr<Animation> FindAnimation(ResourceManagerPlus* resourceManager);
};

