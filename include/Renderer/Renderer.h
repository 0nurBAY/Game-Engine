// //Renderer.h
#pragma once
#include <glm/glm.hpp>
#include <glad/gl.h>
#include "Scene/Scene.h"
#include "Renderer/Camera.h"
#include "Resource/ResourceManagerPlus.h"
#include "Renderer/SpriteBatch.h"
#include "Renderer/FrameBuffer.h"
#include "Renderer/ScreenQuad.h"

struct RenderItem{
    Entity* entity;
    unsigned int layer;
    float z;
};
struct RenderLight{
    glm::vec2 position;
    glm::vec4 color;
    float radius;
};


class Renderer
{
private:
    Camera& camera;
    SpriteBatcher batcher;
    std::vector<RenderItem> items;
    std::vector<RenderLight> lights;
    FrameBuffer framebuffer;
    ScreenQuad screenquad;
    Shader PostProcesserShader;
    float Resx;
    float Resy;
public:
    Renderer(Camera& camera,int width,int height,const char* vertex,const char* fragment);

    void Draw(Scene& scene,ResourceManagerPlus& resourcemanager);
    void SetProjection (int width, int height);
    void ApplyProjectionMatrix(Shader* shader,glm::vec4 ambient);
    void PostProcess();
    void CheckError(const char* where);
};
