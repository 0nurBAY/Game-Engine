//RendererComponent.h
#pragma once
#include "Scene/Components/Component.h"

class RendererComponent : public Component
{
private:
    unsigned int layer;
    float depht_offset;
public:
    RendererComponent(unsigned int new_layer,float depht_offset);
    void SetLayer(unsigned int new_layer);
    void SetOffset    (float depht_offset);
    unsigned int  GetLayer();
    float         GetOffset();
    CopmonentCategory GetCategory() const override;
};
