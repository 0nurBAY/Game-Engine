//FrameBuffer.cpp

#include "Renderer/FrameBuffer.h"
#include <glad/gl.h>
#include <iostream>
FrameBuffer::FrameBuffer(int width, int height):width(width),height(height){
    glGenFramebuffers(1,&FBO);
    glBindFramebuffer(GL_FRAMEBUFFER,FBO);

    glGenTextures(1,&colorTexture);
    glBindTexture(GL_TEXTURE_2D,colorTexture);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA8,
        width,
        height,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        nullptr
    );

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,colorTexture,0);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        std::cout<<"Frame Buffer'da sıkıntı var\n";
    }

    glBindFramebuffer(GL_FRAMEBUFFER,0);
    glBindTexture(GL_TEXTURE_2D,0);

}
void FrameBuffer::Resize(int width, int height){
    this->width = width;
    this->height = height;

    glBindTexture(GL_TEXTURE_2D,colorTexture);
    
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA8,
        width,
        height,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        nullptr
    );

    glBindTexture(GL_TEXTURE_2D,0);

}

void FrameBuffer::Bind(){
    glBindFramebuffer(GL_FRAMEBUFFER,FBO);
    glViewport(0, 0, width, height);
}
void FrameBuffer::UnBind(){
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    glViewport(0, 0, width, height);
}


unsigned int FrameBuffer::GetTexture() const{
    return colorTexture;
}
int FrameBuffer::GetWidth() const{
    return width;
}
int FrameBuffer::GetHeight() const{
    return height;
}


FrameBuffer::~FrameBuffer(){
    glDeleteFramebuffers(1,&FBO);
    glDeleteTextures(1,&colorTexture);
}