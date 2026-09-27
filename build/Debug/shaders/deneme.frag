#version 330 core

out vec4 FragColor;
in vec2 TexCoords;
uniform sampler2D Texture;
uniform float time;
uniform float Resx;
uniform float Resy;

    

float random(vec2 st)
{
    return fract(sin(dot(st, vec2(12.9898, 78.233))) * 43758.5453);
}
void main()
{
    FragColor = texture(Texture,TexCoords);
}

