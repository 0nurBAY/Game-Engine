//IndexxBuffer.h

#pragma once

#include <glad/gl.h>
#include <cstddef>

class IndexBuffer
{
private:
    unsigned int EBOID;
    
public:
    IndexBuffer(const unsigned int* indices, std::size_t size);
    IndexBuffer();
    void MaxAddData(unsigned int count);
    void AddData(const unsigned int* indices, std::size_t size);
    ~IndexBuffer();
    void Bind();
    void UnBind();
};

