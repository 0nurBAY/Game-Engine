//Animation.h
#pragma once
#include <vector>
#include <string>

class Animation
{
private:
    std::vector<std::string> frames;
    float frameDuration;
    float timer;

    std::size_t currentFrame;
    bool loop;

public:
    Animation(std::vector<std::string> frames,float frameDuration,bool loop=true);

    void Update(float dt);
    void Reset();

    const std::string& GetCurrentFrame() const;
    bool IsFinished() const;
 
    std::size_t GetCurrentFrameIndex() const;
};
