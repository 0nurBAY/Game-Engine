#version 330 core

    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec2 aTexCoord;
    layout (location = 2) in vec4 aColor;

    out vec2 TexCoord;
    out vec4 Color;
    out vec2 WorldPos;
    
    uniform mat4 view;
    uniform mat4 projection;
    void main()
    {
        gl_Position = projection * view * vec4(aPos, 1.0);
        TexCoord =aTexCoord;
        Color = aColor;
        WorldPos = aPos.xy;
    }