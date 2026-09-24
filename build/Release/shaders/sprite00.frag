
#version 330 core

    #define MAX_LIGHTS 32
    in vec2 TexCoord;
    in vec2 WorldPos;
    in vec4 Color;
    out vec4 FragColor;

    uniform int light_count;
    uniform vec2 LightPos[MAX_LIGHTS];
    uniform vec4 LightColor[MAX_LIGHTS];
    uniform float LightRadius[MAX_LIGHTS];
    uniform sampler2D ourTexture;
    uniform vec4 Ambient;
    
    void main()
    {
        vec4 lighting = Ambient;

        for(int i=0; i<light_count;i++){
            float distance = length(WorldPos - LightPos[i]);
            float effect = 1.0-((distance)/LightRadius[i]);
            effect = clamp(effect,0.0,1.0);
            
            lighting += effect*LightColor[i];
        }
        vec4 BaseColor = texture(ourTexture,TexCoord)*Color;
        FragColor = vec4(BaseColor.rgb*lighting.rgb,BaseColor.a);
    }