//VertexArray.h
#pragma once
#include "glad/gl.h"
class VertexArray
{
private:
    unsigned int VAOID;
public:
    VertexArray();
    ~VertexArray();
    void Bind();
    void UnBind();
    unsigned int GetVAOID() const;
    void AddAttribute(GLuint index,GLint count,GLenum type,GLsizei, const void*);
};


