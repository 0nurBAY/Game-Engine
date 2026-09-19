//VertexBuffer.h
#pragma once

#include <glad/gl.h>
#include <cstddef>

class VertexBuffer
{
private:
    unsigned int VBOID;

public:
    VertexBuffer(const float* vertices, std::size_t size);
    VertexBuffer();
    void AddBuffer(const void* vertices, std::size_t size);
    ~VertexBuffer();
    void Bind();
    void UnBind();
};
