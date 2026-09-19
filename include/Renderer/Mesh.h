//Mesh.h
#pragma once

#include <cstddef>

#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"

class Mesh{

private:

    bool hasUV;

    VertexArray VAO;
    VertexBuffer VBO;
    IndexBuffer EBO;

    std::size_t indexCount;
public:
    Mesh(
        const float* vertices,
        std::size_t vertexSize,
        const unsigned int* indices,
        std::size_t indexSize,
        bool hasUV = false
    );
    ~Mesh() = default;
    void Bind();
    void UnBind();
    int GetIndexCount() const;
};