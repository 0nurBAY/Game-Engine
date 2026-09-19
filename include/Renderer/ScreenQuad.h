//ScreenQuad.h

#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"

class ScreenQuad
{
private:
    VertexArray VAO;
    VertexBuffer VBO;
    IndexBuffer EBO;

public:
    ScreenQuad();
    
    void Draw();
};

