//SpriteBatch.h
#pragma once
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include <string>
#include <vector>

#include <glm/glm.hpp>
struct SpriteVertex{
    glm::vec3 position;
    glm::vec2 TexCoords;
    glm::vec4 color;
};

class SpriteBatcher
{
private:
    IndexBuffer  EBO;
    VertexArray  VAO;
    VertexBuffer VBO;

    std::vector<SpriteVertex> vertexes;
    

    Shader* currentShader = nullptr;
    Texture* currentTexture = nullptr;
    unsigned int spritecount = 0;

    static constexpr unsigned int MaxSprite = 1000;
public:
    SpriteBatcher();
    void AddSprite(
        const glm::vec2 pos,
        const glm::vec2 size,
        const glm::vec2 uvMin,
        const glm::vec2 uvMax,
        const glm::vec4 color
    );

    void End();
    void Begin();
    void Flush();

};
