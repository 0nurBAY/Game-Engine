//AnimationComponent.h
#pragma once 

#include "Scene/Components/Component.h"
#include "Core/Animation.h"
#include "Resource/AssetHandle.h"
#include <unordered_map>
class AnimationComponent: public Component
{
private:
    std::unordered_map<std::string,AssetHandle<Animation>> animations;
    std::string current_animation;
    std::string request;
    bool reset = 0;
    
public:
    AnimationComponent();
    void AddAnimation(const std::string name, const AssetHandle<Animation>& animation);
    void AnimationUpdate(float dt,ResourceManagerPlus* resourceManager) override;
    void RequestAnimation(const std::string& name);
    void Play(ResourceManagerPlus* resourceManager);
    void Reset();
    std::shared_ptr<Animation> FindAnimation(ResourceManagerPlus* resourceManager);
};

