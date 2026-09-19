//Shader.cpp
#include "Renderer/Shader.h"
#include <iostream>
Shader::Shader(const char* vertexShaderSource, const char* fragmentShaderSource){
    //VertexShader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,nullptr);
    glCompileShader(vertexShader);

    //FragmentShader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSource,nullptr);
    glCompileShader(fragmentShader);

    //ShaderProgram
    ProgramID = glCreateProgram();
    glAttachShader(ProgramID,vertexShader);
    glAttachShader(ProgramID,fragmentShader);
    glLinkProgram(ProgramID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}
Shader::Shader():ProgramID(0){}
void Shader::SetSources(const char *vertexShaderSource, const char *fragmentShaderSource){
//VertexShader
    if(ProgramID != 0){
        glDeleteProgram(ProgramID);
        ProgramID = 0;
    }
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,nullptr);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success){
        glGetShaderInfoLog(
            vertexShader,
            512,
            nullptr,
            infoLog
        );

        std::cout << "VERTEX SHADER ERROR:\n"
                  << infoLog << "\n";
    }
    //FragmentShader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSource,nullptr);
    glCompileShader(fragmentShader);
    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if(!success){
        glGetShaderInfoLog(
            fragmentShader,
            512,
            nullptr,
            infoLog
        );

        std::cout << "FRAGMENT SHADER ERROR:\n"
                  << infoLog << "\n";
    }
    //ShaderProgram
    ProgramID = glCreateProgram();
    glAttachShader(ProgramID,vertexShader);
    glAttachShader(ProgramID,fragmentShader);
    glLinkProgram(ProgramID);

    if(!success){
        glGetProgramInfoLog(
            ProgramID,
            512,
            nullptr,
            infoLog
        );

        std::cout << "SHADER PROGRAM LINK ERROR:\n"
                  << infoLog << "\n";
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


}
Shader::~Shader(){
    glDeleteProgram(ProgramID);
}

void Shader::Use(){
    glUseProgram(ProgramID);
}

unsigned int Shader::GetID(){
    return ProgramID;
}

void Shader::SetMat4(const char *name, const glm::mat4 &value){
    
    int model_location = glGetUniformLocation(ProgramID, name);
    glUniformMatrix4fv(
        model_location,
        1,
        GL_FALSE,
        &value[0][0]
    );
}

void Shader::SetInt(const char *name, int value){
    Use();
    glUniform1i(glGetUniformLocation(ProgramID,name),value);   
}
void Shader::SetFloat(const char *name, float value){
    Use();
    glUniform1f(glGetUniformLocation(ProgramID,name),value);
}
void Shader::SetVec4(const char *name, const glm::vec4 &value){
    Use();
    glUniform4f(glGetUniformLocation(ProgramID,name),value.x, value.y, value.z, value.w);
}
void Shader::SetVec2(const char *name, const glm::vec2 &value){
    Use();
    glUniform2f(glGetUniformLocation(ProgramID,name),value.x, value.y);
}