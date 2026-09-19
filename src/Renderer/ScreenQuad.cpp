//ScreenQuad.cpp

#include "Renderer/ScreenQuad.h"
#include <iostream>
ScreenQuad::ScreenQuad(){
    float vertices[] = {
        -1.0f,1.0f,  0.0f,1.0f,
        -1.0f,-1.0f, 0.0f,0.0f,
         1.0f,-1.0f, 1.0f,0.0f,
         1.0f,1.0f,  1.0f,1.0f,
    };

    unsigned int indices[] = {
        0,1,2,
        0,3,2
    };
    VBO.AddBuffer(vertices,sizeof(float)*16);

    VAO.Bind();
    VBO.Bind();
    VAO.AddAttribute(
        0,
        2,
        GL_FLOAT,
        4* sizeof(float),
        (void*)0
    );
    VAO.AddAttribute(
        1,
        2,
        GL_FLOAT,
        4* sizeof(float),
        (void*)(2*sizeof(float))
    );

    EBO.AddData(indices,sizeof(indices));
    EBO.Bind();
}
void ScreenQuad::Draw(){
    VAO.Bind();

    glDrawElements(
        GL_TRIANGLES,
        6,
        GL_UNSIGNED_INT,
        nullptr
    );
    
}