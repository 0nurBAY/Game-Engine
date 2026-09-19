//VertexBuffer.cpp
#include "Renderer/VertexBuffer.h"


VertexBuffer::VertexBuffer(const float* vertices, std::size_t size){
    glGenBuffers(1,&VBOID);
    Bind();
    glBufferData(
        GL_ARRAY_BUFFER,
        size,
        vertices,
        GL_STATIC_DRAW
    );
}

VertexBuffer::VertexBuffer(){
    glGenBuffers(1,&VBOID);
}
void VertexBuffer::AddBuffer(const void *vertices, size_t size){
    Bind();
    glBufferData(
        GL_ARRAY_BUFFER,
        size,
        vertices,
        GL_DYNAMIC_DRAW
    );
}
VertexBuffer::~VertexBuffer(){
    glDeleteBuffers(1,&VBOID);
}

void VertexBuffer::Bind(){
    glBindBuffer(GL_ARRAY_BUFFER,VBOID);
}

void VertexBuffer::UnBind(){
    glBindBuffer(GL_ARRAY_BUFFER,0);
}