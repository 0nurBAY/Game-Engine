//DebugRenderer.h

#pragma once

#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/Shader.h"

#include <glm/glm.hpp>
#include <glad/gl.h>
#include <vector>

struct DebugData{
    glm::vec2 pos1;
    glm::vec2 pos2;
    glm::vec4 color;
};

class DebugRenderer{

private:
    std::vector<DebugData> Debugdata;
    VertexArray VAO;
    VertexBuffer VBO;
    Shader shader;
public:
    DebugRenderer(const char* vertexShaderSource,const char* fragmentShaderSource);
    void BeginFrame();
    void DrawLine(glm::vec2 pos1,glm::vec2 pos2,glm::vec4 color);
    void DrawCircle(glm::vec2 center,float radius,glm::vec4 color);
    void DrawPoint(glm::vec2 pos,glm::vec4 color);
    void DrawAABB(glm::vec2 min,glm::vec2 max,glm::vec4 color);
    void Flush(const glm::mat4& projection,const glm::mat4& view);
    

};