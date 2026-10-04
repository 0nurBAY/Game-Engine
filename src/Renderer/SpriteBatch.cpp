//SpriteBatch.cpp

#include "Renderer/SpriteBatch.h"
#include <cstddef>
void SpriteBatcher::AddSprite(glm::vec2 pos, glm::vec2 size,float rotation, glm::vec2 uvMin, glm::vec2 uvMax, glm::vec4 color){
    const float rad = glm::radians(rotation);
    const float rcos = glm::cos(rad);
    const float rsin = glm::sin(rad);
    glm::vec2 leftb = glm::vec2((size.x * -0.5f)*rcos-(size.y*-0.5f)*rsin,(size.y*-0.5f)*rcos+(size.x * -0.5f)*rsin);
    glm::vec2 rightb = glm::vec2((size.x * 0.5f)*rcos-(size.y*-0.5f)*rsin,(size.y*-0.5f)*rcos+(size.x * 0.5f)*rsin);
    glm::vec2 leftt = glm::vec2((size.x * -0.5f)*rcos-(size.y*0.5f)*rsin,(size.y*0.5f)*rcos+(size.x * -0.5f)*rsin);
    glm::vec2 rightt = glm::vec2((size.x * 0.5f)*rcos-(size.y*0.5f)*rsin,(size.y*0.5f)*rcos+(size.x * 0.5f)*rsin);
    leftb += pos;
    rightb += pos;
    leftt += pos;
    rightt += pos;
    vertexes.push_back({
        {leftb,0.0f},{uvMin.x,uvMin.y},color
    });
    vertexes.push_back({
        {rightb,0.0f},{uvMax.x,uvMin.y},color
    });
    vertexes.push_back({
        {leftt,0.0f},{uvMin.x,uvMax.y},color
    });
    vertexes.push_back({
        {rightt,0.0f},{uvMax.x,uvMax.y},color
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