//RendererComponent.h
#pragma once
#include "Scene/Components/Component.h"

class RendererComponent : public Component
{
private:
    unsigned int layer;
    float z;
public:
    RendererComponent(unsigned int new_layer,float z);
    void SetLayer(unsigned int new_layer);
    void SetZ    (float new_z);
    unsigned int  GetLayer();
    float         GetZ();
};
