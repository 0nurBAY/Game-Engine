#version 330 core

    in vec2 LocalPos;
    out vec4 FragColor;

    uniform vec4      gradientCenter;
    uniform vec4      gradientEdge;
    void main()
    {
        float distance = length(LocalPos)/200.0;
        distance = clamp(distance, 0.0,1.0);
        FragColor = mix(gradientCenter,gradientEdge,distance);
    }