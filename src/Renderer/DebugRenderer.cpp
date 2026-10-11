//DebugRenderer.cpp

#include "Renderer/DebugRenderer.h"
DebugRenderer::DebugRenderer(const char *vertexShaderSource, const char *fragmentShaderSource)
{
    shader.SetSources(vertexShaderSource,fragmentShaderSource);
    VAO.Bind();
    VBO.Bind();
    
    VAO.AddAttribute(
        0,
        2,
        GL_FLOAT,
        6* sizeof(float),
        (void*)0
    );
    VAO.AddAttribute(
        1,
        4,
        GL_FLOAT,
        6* sizeof(float),
        (void*)(2*sizeof(float))
    );
    VAO.UnBind();
    VBO.UnBind();
}
void DebugRenderer::BeginFrame(){
    Debugdata.clear(); 
}
void DebugRenderer::DrawLine(glm::vec2 pos1, glm::vec2 pos2, glm::vec4 color){
    Debugdata.push_back({pos1,pos2,color});
}

void DebugRenderer::DrawCircle(glm::vec2 center, float radius, glm::vec4 color){
    for(int i= 0; i<32;i++){
        glm::vec2 pos1 = glm::vec2(radius*glm::cos(i * glm::two_pi<float>() /32),radius*glm::sin(i * glm::two_pi<float>() /32));
        glm::vec2 pos2 = glm::vec2(radius*glm::cos((i+1) * glm::two_pi<float>() /32),radius*glm::sin((i+1) * glm::two_pi<float>() /32));
        DrawLine(pos1+center,pos2+center,color);
    }
}
void DebugRenderer::DrawPoint(glm::vec2 pos, glm::vec4 color){
    DrawLine(pos+glm::vec2(5,0),pos-glm::vec2(5,0),color);
    DrawLine(pos+glm::vec2(0,5),pos-glm::vec2(0,5),color);
}
void DebugRenderer::DrawBox(glm::vec2 min, glm::vec2 max, glm::vec4 color){
    DrawLine(min,glm::vec2(min.x,max.y),color);
    DrawLine(min,glm::vec2(max.x,min.y),color);
    DrawLine(max,glm::vec2(min.x,max.y),color);
    DrawLine(max,glm::vec2(max.x,min.y),color);
}

void DebugRenderer::Flush(
    const glm::mat4 &projection,
    const glm::mat4 &view
){
    if(Debugdata.empty()) return;
    std::vector<float> vertices;
    vertices.reserve(Debugdata.size()*12);

    for(auto& debug:Debugdata){
        vertices.push_back(debug.pos1.x);
        vertices.push_back(debug.pos1.y);

        vertices.push_back(debug.color.r);
        vertices.push_back(debug.color.g);
        vertices.push_back(debug.color.b);
        vertices.push_back(debug.color.a);

        // İkinci vertex
        vertices.push_back(debug.pos2.x);
        vertices.push_back(debug.pos2.y);

        vertices.push_back(debug.color.r);
        vertices.push_back(debug.color.g);
        vertices.push_back(debug.color.b);
        vertices.push_back(debug.color.a);
    }
    VBO.AddBuffer(vertices.data(),sizeof(float)*vertices.size());
    
    shader.Use();
    shader.SetMat4("projection",projection);
    shader.SetMat4("view",view);

    VAO.Bind();
    glLineWidth(3.0f);
    glDrawArrays(
        GL_LINES,
        0,
        static_cast<GLsizei>(vertices.size() / 6)
    );
    glLineWidth(1.0f);
    VAO.UnBind();
}
