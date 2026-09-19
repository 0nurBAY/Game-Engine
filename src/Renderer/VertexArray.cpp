//VertexArray.cpp
#include "Renderer/VertexArray.h"

VertexArray::VertexArray(/* args */){
    glGenVertexArrays(1,&VAOID);
    Bind();
}

VertexArray::~VertexArray(){
    glDeleteVertexArrays(1,&VAOID);
}

void VertexArray::Bind(){
    glBindVertexArray(VAOID);
}

void VertexArray::UnBind(){
    glBindVertexArray(0);
    
}

void VertexArray::AddAttribute(GLuint index,GLint count,GLenum type,GLsizei stride, const void* offset){
    glVertexAttribPointer(
        index,
        count,
        type,
        GL_FALSE,
        stride,
        offset
    );
    glEnableVertexAttribArray(index);
}
unsigned int VertexArray::GetVAOID() const{
    return VAOID;
}