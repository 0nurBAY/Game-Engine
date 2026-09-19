//FrameBuffer.h

#pragma once

class FrameBuffer
{
private:
    unsigned int FBO;
    unsigned int colorTexture;
    int width;
    int height;
public:
    FrameBuffer(int width, int height);
    ~FrameBuffer();
    
    unsigned int GetTexture () const;
    int GetWidth            () const;
    int GetHeight           () const;

    void Bind();
    void UnBind();

    void Resize(int width, int height);
};
