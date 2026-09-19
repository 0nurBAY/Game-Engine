//HandsScript.h

#pragma once

#include "Core/Script/Script.h"
#include <queue>
class HandsScript : public Script
{
private:
    std::queue<char> signs;
public:
    void AddSign(char sign);
    void ApplySignes();
    void OnEvent(Event& event) override;

};

