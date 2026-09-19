//Mesh.cpp

#include "Renderer/Mesh.h"

Mesh::Mesh(const float* vertices, size_t vertexSize, const unsigned int* indices, size_t indexSize, bool hasUV):
VAO(),
VBO(vertices,vertexSize),
EBO(indices,indexSize),
indexCount(indexSize / sizeof(unsigned int))
{
    std::size_t stride;
    VAO.Bind();
    VBO.Bind();
    
    if(hasUV) stride = 5;
    else stride = 3;

    VAO.AddAttribute(0,
        3,
        GL_FLOAT,
        (stride)*sizeof(float),
        (void*)0);
    if(stride==5){
        VAO.AddAttribute(1,
            2,
            GL_FLOAT,
            stride*sizeof(float),
            (void*)(3*sizeof(float)));
    }

    EBO.Bind();
    VAO.UnBind();
    VBO.UnBind();
}

void Mesh::Bind(){
    VAO.Bind();
}
void Mesh::UnBind(){
    VAO.UnBind();
}


int Mesh::GetIndexCount() const{
    return int(indexCount);
}