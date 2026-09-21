//ScriptManager.cpp
#include "Core/ScriptManager.h"
#include "Core/Script/PlayerScript.h"
#include "Core/Script/TestScript2.h"
#include "Core/Script/CameraScript.h"
#include "Core/Script/HandsScript.h"
std::unique_ptr<Script> ScriptManager::CreateScript(const std::string &name){
    auto it = scripts.find(name);
    if(it==scripts.end()) return nullptr;
    auto script = it->second();
    return std::move(script);
}
void ScriptManager::Init(){
    scripts.emplace("PlayerScript",[]{
        return std::make_unique<PlayerScript>();
    });
    scripts.emplace("NPC1Script",[]{
        return std::make_unique<TestScript2>();
    });
    scripts.emplace("CameraScript",[]{
        return std::make_unique<CameraScript>();
    });
    scripts.emplace("HandScript",[]{
        return std::make_unique<HandsScript>();
    });
}