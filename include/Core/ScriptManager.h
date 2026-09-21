//ScriptManager.h
#pragma once
#include "Core/Script/Script.h"
#include <unordered_map>
#include <string>
#include <functional>
#include <memory>
class ScriptManager
{
private:
    std::unordered_map<std::string,std::function<std::unique_ptr<Script>()>> scripts;
public:
    std::unique_ptr<Script> CreateScript(const std::string& name);
    void Init();
};
