//SpriteBatch.cpp

#include "Renderer/SpriteBatch.h"
#include <cstddef>
void SpriteBatcher::AddSprite(glm::vec2 pos, glm::vec2 size, glm::vec2 uvMin, glm::vec2 uvMax, glm::vec4 color){
    
    vertexes.push_back({
        {pos.x-size.x * 0.5f,pos.y-size.y*0.5f,0.0f},{uvMin.x,uvMin.y},color
    });
    vertexes.push_back({
        {pos.x+size.x * 0.5f,pos.y-size.y*0.5f,0.0f},{uvMax.x,uvMin.y},color
    });
    vertexes.push_back({
        {pos.x-size.x * 0.5f,pos.y+size.y*0.5f,0.0f},{uvMin.x,uvMax.y},color
    });
    vertexes.push_back({
        {pos.x+size.x * 0.5f,pos.y+size.y*0.5f,0.0f},{uvMax.x,uvMax.y},color
    });
    spritecount++;
    if(spritecount==MaxSprite)Flush();
}
void SpriteBatcher::Begin(){
}
void SpriteBatcher::Flush(){
    if(spritecount==0)return;
    VBO.AddBuffer(
        vertexes.data(),vertexes.size()* sizeof(SpriteVertex)
    );
    VAO.Bind();
    glDrawElements(
        GL_TRIANGLES,
        spritecount*6,
        GL_UNSIGNED_INT,
        nullptr
    );
    vertexes.clear();
    spritecount = 0;
}
SpriteBatcher::SpriteBatcher(){
    
    VAO.Bind();
    VBO.Bind();
    VAO.AddAttribute(0,3,GL_FLOAT,sizeof(SpriteVertex),(void*)offsetof(SpriteVertex,position));
    VAO.AddAttribute(1,2,GL_FLOAT,sizeof(SpriteVertex),(void*)offsetof(SpriteVertex,TexCoords));
    VAO.AddAttribute(2,4,GL_FLOAT,sizeof(SpriteVertex),(void*)offsetof(SpriteVertex,color));
    EBO.Bind();
    EBO.MaxAddData(MaxSprite);

}