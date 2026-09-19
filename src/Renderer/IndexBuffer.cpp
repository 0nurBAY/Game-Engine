
//IndexBuffer.cpp
#include "Renderer/IndexBuffer.h"
#include <vector>
IndexBuffer::IndexBuffer(const unsigned int* indices, std::size_t size)
{
    glGenBuffers(1,&EBOID);
    Bind();
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        size,
        indices,
        GL_STATIC_DRAW
    );
}
IndexBuffer::IndexBuffer(){
    glGenBuffers(1,&EBOID);
}
void IndexBuffer::MaxAddData(unsigned int count){
    Bind();
    std::vector<unsigned int> indices;
    indices.reserve(count*6);
    for(int i=0;i < count; i++){
        indices.push_back(0+i*4);
        indices.push_back(1+i*4);
        indices.push_back(2+i*4);
        indices.push_back(1+i*4);
        indices.push_back(2+i*4);
        indices.push_back(3+i*4);
    }
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        indices.size()*sizeof(unsigned int),
        indices.data(),
        GL_STATIC_DRAW
    );
}
void IndexBuffer::AddData(const unsigned int *indices, size_t size){
    Bind();
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        size,
        indices,
        GL_STATIC_DRAW
    );
}


IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1,&EBOID);
}

void IndexBuffer::Bind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBOID);

}

void IndexBuffer::UnBind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}
