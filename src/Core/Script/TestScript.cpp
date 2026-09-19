//TestScript.cpp
#include "Core/Script/TestScript.h"
#include "Scene/Entity.h"

void TestScript::Update(float deltatime){
    auto* e = GetEntity(); 
    auto* transform = e->GetComponent<TransformComp>();
    if(!transform) return;
    transform->position.x += 100.0f *deltatime;
}
