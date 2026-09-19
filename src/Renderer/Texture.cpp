//Texture.cpp

#include "Renderer/Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <stdexcept>
#include <iostream>
Texture::Texture(const char* path)
{
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path,&width,&height,&channels,0);
    if(!data){
        std::cout<< "Texture yükleme hatası"<<path<< "\n";
        std::cout << "STB: " << stbi_failure_reason() << "\n";
        throw std::runtime_error("Texture yükleme hatası");
    }
    GLenum format;
    if(channels == 4) {format = GL_RGBA;}
    else if(channels == 3) {format = GL_RGB; }
    else { 
        stbi_image_free(data);
        std::cout<< "Desteklenmeyen Format\n";

        throw std::runtime_error("Desteklenmeyen Format");
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D,textureID);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);


    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        format,
        width,
        height,
        0,
        format,
        GL_UNSIGNED_BYTE,
        data
    );

    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

}

Texture::~Texture()
{
    glDeleteTextures(1,&textureID);
}


void Texture::Bind(unsigned int slot) const{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D,textureID);
}

void Texture::UnBind() const{
    glBindTexture(GL_TEXTURE_2D,0);
}

GLuint Texture::GetID() const
{
    return textureID;
}

int Texture::GetWidth() const
{
    return width;
}

int Texture::GetHeight() const
{
    return height;
}

Texture::Texture(Texture&& other) noexcept
    : textureID(other.textureID), width(other.width), height(other.height), channels(other.channels)
{
    other.textureID = 0;
}

Texture& Texture::operator=(Texture&& other) noexcept
{
    if (this != &other) {
        glDeleteTextures(1, &textureID);
        textureID = other.textureID;
        width = other.width;
        height = other.height;
        channels = other.channels;
        other.textureID = 0;
    }
    return *this;
}