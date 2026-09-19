//Shader.h
#pragma once

#include <glm/glm.hpp>
#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp> 


class Shader
{
private:
    unsigned int ProgramID;

public:
    Shader(const char* vertexShaderSource,const char* fragmentShaderSource);
    Shader();
    ~Shader();
    void Use();
    unsigned int GetID();
    void SetSources(const char* vertexShaderSource,const char* fragmentShaderSource);
    void SetMat4    (const char* name, const glm::mat4& value);
    void SetInt     (const char* name, int   value);
    void SetFloat   (const char* name, float value);
    void SetVec4    (const char* name, const glm::vec4& value);
    void SetVec2    (const char* name, const glm::vec2& value);
};
