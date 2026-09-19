//ScriptComponent.h
#pragma once
#include "Scene/Components/Component.h"
#include "Core/Script/Script.h"
#include "Resource/AssetHandle.h"
#include <memory>

class ScriptComponent : public Component
{
private:
    std::unique_ptr<Script> script;
public:
    ScriptComponent(std::unique_ptr<Script> script);
    void SetEntity(Entity* entity);
    void SetInput(Input* input);
    void Update(float dt) override;
    template<typename T> T* GetScript();
    void OnCreate() override;
    void OnDestroy() override;
    void OnEvent(Event& event) override;
};
#include "Scene/Components/ScriptComponent.inl"