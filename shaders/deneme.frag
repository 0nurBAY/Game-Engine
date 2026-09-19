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
    //Kıvrım
    vec2 uv = TexCoords*2.0 -1.0;
    float x = uv.x;
    float y = uv.y;
    uv *= 1.0 + 0.08 * (uv.x*uv.x + uv.y*uv.y);
    uv = uv*0.5 +0.5;
    if(uv.x<0.0||uv.x>1.0){
        FragColor =vec4(0.0);
        return;
    }
    ////Jitter bozulma
    float jitter = sin(random(vec2(gl_FragCoord.y,floor(time*10.0))))*0.003;
    uv.x += jitter;
    ////Kıvrımı atama
    vec4 color = texture(Texture,uv);
    float distance = length(vec2(0.5) - uv);
//
    ////RGB kayma
    float r = texture(Texture,uv+vec2(0.0025,0.0)).r;
    float g = texture(Texture,uv).g;
    float b = texture(Texture,uv-vec2(0.003,0.0)).b;
    color.rgb = vec3(r,g,b);
//
    ////Blur
    ////vec4 blur = color;
    ////blur += texture(Texture,uv+vec2(1/Resx,0.0));
    ////blur += texture(Texture,uv+vec2(-1/Resx,0.0));
    ////blur += texture(Texture,uv+vec2(0.0,1/Resy));
    ////blur += texture(Texture,uv+vec2(0.0,-1/Resy));
    ////blur *= 0.2;
    ////color = color*0.4 + blur*0.6;
    //
//
    ////çok hafif parlama
    float flick = sin(time*10.0);
    color.rgb *= 1.0 + flick*0.02;
//
    ////float effect = smoothstep(0.3,0.7,distance);
    ////color.rgb *= 1.0-effect*0.8;
//
//
    ////float noise = random(uv) -0.5;
    ////noise *= 0.05;
    ////color.rgb += noise;
//
//
    //float scanliney = smoothstep(0.35,0.6,fract(gl_FragCoord.y/10.0)*2.0);
    float scanliney =sin(gl_FragCoord.y*0.6);
    color.rgb *= 0.9 +scanliney*0.5;
    
    //float scanlinex =max(sin(0.5*gl_FragCoord.x),0)-max(-(asin(sin(0.5*gl_FragCoord.x))*0.63661)*2.0,0); 
    //
    float scanlinex = smoothstep(0.35,0.45,fract(gl_FragCoord.x/15.0)*2.0);
    color.rgb *= 0.9 +scanlinex*0.1;

    FragColor = color;
}

