//Animation.cpp

#include "Core/Animation.h"
#include <iostream>
Animation::Animation(std::vector<std::string> frames, float frameDuration, bool loop):
frames(frames),
frameDuration(frameDuration),
timer(0.0f),
currentFrame(0),
loop(loop){
    if(this->frameDuration<=0) this->frameDuration = 0.1f;
}


void Animation::Update(float dt){
    if(frames.empty())return;
    if(IsFinished())return;

    timer+=dt;
    while(timer >= frameDuration){
        timer -= frameDuration;
        currentFrame++;
        if(currentFrame>=frames.size()){
            if(loop){
                currentFrame = 0;
            }else{
                currentFrame = frames.size()-1;
                break;
            }

        }
    }
}

void Animation::Reset(){
    timer = 0.0f;
    currentFrame = 0;
}

const std::string &Animation::GetCurrentFrame() const{
    return frames[currentFrame];
}
size_t Animation::GetCurrentFrameIndex() const{
    return currentFrame;
}
bool Animation::IsFinished() const{
    return !loop && currentFrame == frames.size()-1;
}