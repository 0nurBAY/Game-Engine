//Renderer.cpp
#include "Renderer/Renderer.h"
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
    glm::vec4 ambient = glm::vec4(0.0f);
    Shader*  currentshader = nullptr;
    Texture* currenttexture = nullptr;
    Texture* currentnormal = nullptr;
    for (auto& [id,entity] : scene.GetEntityManager().GetEntites()){
        if (entity->HasComponent<AmbientLightComponent>()){
            ambient = entity->GetComponent<AmbientLightComponent>()->GetColor();
            continue;
        }
        if (entity->HasComponent<LightComponent>()&&entity->HasComponent<TransformComp>()){
            TransformComp *transformComp = entity->GetComponent<TransformComp>();
            LightComponent *lightcomp    = entity->GetComponent<LightComponent>();
            lights.push_back({
                transformComp->position,
                lightcomp->GetColor(),
                lightcomp->GetRadius()
            });
            continue;
        }
        if (!entity->HasComponent<RendererComponent>())continue;
        items.push_back({
            entity.get(),
            entity->GetComponent<RendererComponent>()->GetLayer(),
            -entity->GetComponent<TransformComp>()->position.y
        });
    }
    std::sort(items.begin(),items.end(),
        [](const RenderItem& a, const RenderItem& b){
            if(a.layer!=b.layer) return a.layer<b.layer;
            else if(a.z!=b.z) return a.z<b.z;
            else return a.entity->GetID()<b.entity->GetID();
        });
    
    // for (auto& [entity,layer,z] : items){
    //     TransformComp     *transformComp = entity->GetComponent<TransformComp>      ();
    //     MeshComponent     *meshComp      = entity->GetComponent<MeshComponent>      ();
    //     MaterialComponent *materialComp  = entity->GetComponent<MaterialComponent>  ();
    //     SpriteComponent   *spriteComp    = entity->GetComponent<SpriteComponent>    ();
    //     if(!transformComp||!meshComp||!materialComp) continue;
    //     auto mesh     = resourcemanager.Resolve<Mesh>    (meshComp->GetMesh().GetName());
    //     auto material = resourcemanager.Resolve<Material>(materialComp->GetMaterial().GetName());
    //     auto new_shader = resourcemanager.Resolve<Shader>(material->GetShader().GetName());
    //     if(!mesh||!material||!new_shader) continue;

    //     if(currentshader != new_shader.get()){
    //         currentshader = new_shader.get();
    //         ApplyProjectionMatrix(currentshader);
    //     }

    //     if(spriteComp){
    //         auto atlas = resourcemanager.Resolve<TextureAtlas>(spriteComp->GetAtlas().GetName());
    //         AtlasUV uv = atlas->GetUV(spriteComp->GetSprite());
    //         currentshader->SetVec2("uvMax",uv.max);
    //         currentshader->SetVec2("uvMin",uv.min);
    //     }else{
    //         currentshader->SetVec2("uvMax",glm::vec2(1.0f,1.0f));
    //         currentshader->SetVec2("uvMin",glm::vec2(0.0f,0.0f));
    //     }
    //     glm::mat4 model = glm::mat4(1.0f);
    //     model = glm::translate  (model, glm::vec3(transformComp->position,0.0f));
    //     model = glm::rotate     (model, glm::radians(transformComp->rotation), glm::vec3(0,0,1));
    //     model = glm::scale      (model, glm::vec3(transformComp->scale, 1.0f));
    //     currentshader->SetMat4("model",model);
    //     material->Apply(resourcemanager);
    //     mesh->Bind();

    //     glDrawElements(
    //         GL_TRIANGLES,
    //         mesh->GetIndexCount(),
    //         GL_UNSIGNED_INT,
    //         (void*)0
    //     );
    // }
    framebuffer.Bind();
    glClear(GL_COLOR_BUFFER_BIT);
    for (auto& [entity,layer,z] : items){
        TransformComp     *transformComp = entity->GetComponent<TransformComp>      ();
        MaterialComponent *materialComp  = entity->GetComponent<MaterialComponent>  ();
        SpriteComponent   *spriteComp    = entity->GetComponent<SpriteComponent>    ();
        if(!transformComp||!materialComp) continue;

        auto material = resourcemanager.Resolve<Material>(materialComp->GetMaterial().GetName());
        auto new_shader  = resourcemanager.Resolve<Shader>(material->GetShader().GetName());
        auto new_texture = resourcemanager.Resolve<Texture>(material->GetTexture().GetName());
        auto new_normal  = resourcemanager.Resolve<Texture>(material->GetNormal().GetName());
        if(!material||!new_shader||!new_texture) continue;
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
            batcher.AddSprite(transformComp->position,glm::vec2(it->w,it->h)*transformComp->scale,uv.min,uv.max,glm::vec4(1.0f,1.0f,1.0f,1.0f)
            );
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

