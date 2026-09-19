//Texture.h
#pragma once

#include <glad/gl.h>

class Texture
{
private:
    GLuint textureID;
    int width;
    int height;
    int channels;
public:
    Texture(const char* path);
    ~Texture(); 

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    Texture(Texture&& other) noexcept;
    Texture& operator=(Texture&& other) noexcept;
    void Bind   (unsigned int slot) const;
    void UnBind () const;

    GLuint  GetID       () const;
    int     GetWidth    () const;
    int     GetHeight   () const;

};

