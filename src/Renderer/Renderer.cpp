//Renderer.cpp
#include "Renderer/Renderer.h"
#include "Scene/Components/ComponentCategory.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <GLFW/glfw3.h>
Renderer::Renderer(Camera &camera,int width,int height,const char* vertex,const char* fragment):camera(camera),framebuffer(width,height),Resx(width),Resy(height)
{
    batcher.Begin();
    PostProcesserShader.SetSources(vertex,fragment);
}

void Renderer::Draw(Scene &scene, ResourceManagerPlus &resourcemanager){
    items.clear();
    lights.clear();
    items.reserve(scene.GetEntityManager().GetSize());
    auto* cam = scene.GetEntityCamera();
    float cam_widht = cam->GetWidth()*0.5f  *cam->GetZoom() + 200.0f;
    float cam_height = cam->GetHeight()*0.5f*cam->GetZoom() + 200.0f;
    glm::vec4 ambient = glm::vec4(0.7f);
    Shader*  currentshader = nullptr;
    Texture* currenttexture = nullptr;
    Texture* currentnormal = nullptr;
    // int unrendered = 0;
    for (auto& [id,entity] : scene.GetEntityManager().GetEntites()){
        if(!(entity.get()->GetType() & static_cast<uint32_t>(CopmonentCategory::Rendering))) continue;
        if (entity->HasComponent<AmbientLightComponent>()){
            ambient = entity->GetComponent<AmbientLightComponent>()->GetColor();
            continue;
        }
        if(!(entity.get()->GetType() & static_cast<uint32_t>(CopmonentCategory::Transform))) continue;

        if (entity->HasComponent<LightComponent>()){
            TransformComp *transformComp = entity->GetComponent<TransformComp>();
            LightComponent *lightcomp    = entity->GetComponent<LightComponent>();
            lights.push_back({
                transformComp->position,
                lightcomp->GetColor(),
                lightcomp->GetRadius()
            });
            continue;
        }
        glm::vec2 entity_pos = entity->GetComponent<TransformComp>()->position;
        if(std::abs(entity_pos.x - cam->GetPosition().x) > cam_widht ||
           std::abs(entity_pos.y - cam->GetPosition().y) > cam_height){
            //unrendered++;
             continue;}
        items.push_back({
            entity.get(),
            entity->GetComponent<RendererComponent>()->GetLayer(),
            entity->GetComponent<RendererComponent>()->GetOffset()-entity->GetComponent<TransformComp>()->position.y
        });
    }
    // std::cout<< "Unrendered: " << unrendered << "\n";
    std::sort(items.begin(),items.end(),
        [](const RenderItem& a, const RenderItem& b){
            if(a.layer!=b.layer) return a.layer<b.layer;
            else if(a.z!=b.z) return a.z<b.z;
            else return a.entity->GetID()<b.entity->GetID();
        });
    framebuffer.Bind();
    glClear(GL_COLOR_BUFFER_BIT);
    for (auto& [entity,layer,z] : items){
        TransformComp     *transformComp = entity->GetComponent<TransformComp>      ();
        MaterialComponent *materialComp  = entity->GetComponent<MaterialComponent>  ();
        SpriteComponent   *spriteComp    = entity->GetComponent<SpriteComponent>    ();
        if(!transformComp||!materialComp) continue;

        auto material    = resourcemanager.Resolve<Material>(materialComp->GetMaterial().GetName());
        auto new_shader  = resourcemanager.Resolve<Shader>(material->GetShader().GetName());
        auto new_texture = resourcemanager.Resolve<Texture>(material->GetTexture().GetName());
        auto new_normal  = resourcemanager.Resolve<Texture>(material->GetNormal().GetName());
        if(!material||!new_shader||!new_texture) {
            std::cout << "Entity " << entity->GetName() << " Hasn't rendered\n";
            continue;}
        if(currentshader != new_shader.get()){
            batcher.Flush();
            currentshader = new_shader.get();
            ApplyProjectionMatrix(currentshader,ambient);
            material->Apply(resourcemanager);
        }
        if(currenttexture !=new_texture.get()){
            batcher.Flush();
            currenttexture = new_texture.get();
            material->Apply(resourcemanager);
        }
        if(currentnormal !=new_normal.get()){
            batcher.Flush();
            currentnormal = new_normal.get();
            material->ApplyNormal(resourcemanager);
        }
        if(spriteComp){
            auto atlas = resourcemanager.Resolve<TextureAtlas>(spriteComp->GetAtlas().GetName());
            auto it = atlas->GetSprite(spriteComp->GetSprite());
            AtlasUV uv = atlas->GetUV(spriteComp->GetSprite());
            batcher.AddSprite(transformComp->position,glm::vec2(it->w,it->h)*transformComp->scale,transformComp->rotation,uv.min,uv.max,glm::vec4(1.0f,1.0f,1.0f,1.0f));
        }
    }
    batcher.Flush();
    framebuffer.UnBind();
    PostProcess();
}

void Renderer::SetProjection(int width, int height){
    Resx = width;
    Resy = height;
    float aspect = (float)width/(float)height;
    float WorldHeight = 1200.0f;
    float WorldWeight = WorldHeight * aspect;
    
    camera.SetSize(WorldWeight,WorldHeight,width,height);
    framebuffer.Resize(width,height);
}
void Renderer::ApplyProjectionMatrix(Shader *shader,glm::vec4 ambient){
    shader->Use();
    shader->SetMat4("projection",camera.GetProjectionMatrix());
    shader->SetMat4("view",camera.GetViewMatrix());
    shader->SetInt("light_count",lights.size());
    shader->SetVec4("Ambient",ambient);

    for(int i = 0; i<lights.size();i++){
        shader->SetVec2(("LightPos["+std::to_string(i)+"]").c_str(),lights[i].position);
        shader->SetVec4(("LightColor["+std::to_string(i)+"]").c_str(),lights[i].color);
        shader->SetFloat(("LightRadius["+std::to_string(i)+"]").c_str(),lights[i].radius);
    }
}

void Renderer::PostProcess(){
    PostProcesserShader.Use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(
        GL_TEXTURE_2D,
        framebuffer.GetTexture()
    );
    PostProcesserShader.SetInt("Texture",0);
    PostProcesserShader.SetFloat("Resx",Resx);
    PostProcesserShader.SetFloat("Resy",Resy);
    float time = glfwGetTime();
    // std::cout<<time<<"\n";
    PostProcesserShader.SetFloat("time",time);


    screenquad.Draw();
}

