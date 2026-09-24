//AnimationComponent.cpp

#include "Scene/Components/AnimationComponent.h"
#include "Scene/Entity.h"
AnimationComponent::AnimationComponent(){}
void AnimationComponent::AddAnimation(std::string name, const AssetHandle<Animation> &animation){
    if(animations.empty())current_animation = name;
    animations.insert({name,animation});
}
void AnimationComponent::AnimationUpdate(float dt,ResourceManagerPlus* resourceManager){
    
    Play(resourceManager);
    auto animation = FindAnimation(resourceManager);
    if(!animation)return;
    if(reset){
        animation->Reset();
        reset = 0;
    }
    else animation->Update(dt);
    SpriteComponent* spritecomp = owner->GetComponent<SpriteComponent>();
    if(!spritecomp){
        std::cout<<owner->GetName()<<" Entity'sinin SpriteComponenti yok\n";
        return;
    }
    spritecomp->SetSprite(animation->GetCurrentFrame());
}
void AnimationComponent::RequestAnimation(const std::string &name){
    request = name;
}
void AnimationComponent::Play(ResourceManagerPlus* resourceManager){
    if(current_animation==request)return;
    auto old = current_animation;
    current_animation = request;
    auto animation = FindAnimation(resourceManager);
    if(!animation){
        std::cout<<owner->GetName()<<" animation "<<current_animation.c_str()<<" couldn't found\n";
        current_animation = old;
        request = old;
        return;
    }
    animation->Reset();
    reset = 0;
}
void AnimationComponent::Reset(){
    reset = 1;
}
std::shared_ptr<Animation> AnimationComponent::FindAnimation(ResourceManagerPlus* resourceManager){
    auto it = animations.find(current_animation);
    if(it==animations.end()) return nullptr;
    return resourceManager->Resolve<Animation>((it->second).GetName());
}