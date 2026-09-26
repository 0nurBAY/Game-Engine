//AnimationComponent.h
#pragma once 

#include "Scene/Components/Component.h"
#include "Core/Animation.h"
#include "Resource/AssetHandle.h"
#include <unordered_map>
#include <vector>
enum class Directions{
    UP,DOWN,LEFT,RIGHT,
    UPLEFT,UPRIGHT,
    DOWNLEFT,DOWNRIGHT,
    NONE
};
class AnimationComponent: public Component
{
private:
    std::unordered_map<std::string,std::unordered_map<Directions,AssetHandle<Animation>>> animations;
    std::unordered_map<std::string,int> queue;
    std::string current_state;
    std::string request;
    std::vector<std::string> requests;
    bool reset = 0;
    bool dirnon = 0;
    Directions direction =Directions::DOWN;
    Directions directionrequest;
public:
    AnimationComponent();
    void AddAnimation(const std::string state,Directions dir, const AssetHandle<Animation>& animation);
    void AddQueue(const std::string state,uint64_t queue);
    void AnimationUpdate(float dt,ResourceManagerPlus* resourceManager) override;
    void OnEvent(Event& event) override;
    void RequestAnimation(const std::string& name);
    void Play(ResourceManagerPlus* resourceManager);
    void Reset();
    void Decide();
    void SetDirection(Directions drequest);
    std::shared_ptr<Animation> FindAnimation(ResourceManagerPlus* resourceManager);
};

