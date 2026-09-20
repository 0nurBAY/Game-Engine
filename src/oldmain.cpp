//main.cpp
#include "Renderer/Renderer.h"
#include "Window/Window.h"
#include "Window/Time.h"
#include "Core/Input.h"
#include "Event/EventDispatcher.h"
#include "Event/WindowEvent.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"
#include "Resource/ResourceManagerPlus.h"
#include "Core/Script/TestScript.h"
#include "Core/Script/PlayerScript.h"
#include "Core/Script/CameraScript.h"
#include "Core/Script/HandsScript.h"
#include "Core/Script/TestScript2.h"
#include "Core/Animation.h"

#include <iostream>
#include <iomanip>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <fstream>
#include <sstream>

std::string ReadShader(const std::string &path){
    std::ifstream file(path);
    if(!file.is_open()){ std::cout<<"!FILE "<<path<<" couldn't open\n"; return "";}
    std::stringstream shader;
    shader << file.rdbuf();

    file.close();
    return shader.str();

}
int main(){
    std::string vertexShaderSource_sprite = ReadShader("shaders/sprite.vert");
    std::string fragmentShaderSource_sprite_without_normalmap = ReadShader("shaders/sprite00.frag");
    std::string fragmentShaderSource_sprite_with_normalmap    = ReadShader("shaders/sprite01.frag");
    std::string vertexShaderSource_solidcolor  = ReadShader("shaders/solidcolor.vert");
    std::string fragmentShaderSource_solidcolor= ReadShader("shaders/solidcolor.frag");
    std::string vertexShaderSource_gradient    = ReadShader("shaders/gradient.vert");
    std::string fragmentShaderSource_gradient  = ReadShader("shaders/gradient.frag");
    
    std::string vertexShaderSource_postprocesser  = ReadShader("shaders/deneme.vert");
    std::string fragmentShaderSource_postprocesser= ReadShader("shaders/deneme.frag");
    Window window(1200,1200,"Engine");  
    Input input(window);
    Camera camera(window.GetWidth(),window.GetHeight());
    camera.SetPosition(glm::vec3(0.0f,0.0f,0.0f));
    Time time;
    ResourceManagerPlus resoursmanager;
    float npc_x = 600.0f;
    float npc_y = 600.0f;
    
    resoursmanager.IncludeItem<Texture>("CharacterSprites","assets/char_sprites.png");
    resoursmanager.IncludeItem<Texture>("EnviormentSprite","assets/enviorment_sprite2.png");
    AssetHandle<Texture> char_sprite("CharacterSprites");
    AssetHandle<Texture> enviorment_sprite("EnviormentSprite");
    
    resoursmanager.IncludeItem<Texture>("CharacterNormal","assets/char_sprite_normal.png");
    resoursmanager.IncludeItem<Texture>("EnviormentNormal","assets/enviorment_sprite_normal.png");
    AssetHandle<Texture> char_normal("CharacterNormal");
    AssetHandle<Texture> enviorment_normal("EnviormentNormal");

    resoursmanager.IncludeItem<Shader>("2D_sprite_Shader_Normal1"  ,vertexShaderSource_sprite.c_str(),fragmentShaderSource_sprite_with_normalmap.c_str());
    AssetHandle<Shader> sprite_shader_with_normal("2D_sprite_Shader_Normal1");
    
    resoursmanager.IncludeItem<Shader>("2D_sprite_Shader_Normal0"  ,vertexShaderSource_sprite.c_str(),fragmentShaderSource_sprite_without_normalmap.c_str());
    AssetHandle<Shader> sprite_shader_without_normal("2D_sprite_Shader_Normal0");

    resoursmanager.IncludeItem<Material>("PlayerMat");
    resoursmanager.IncludeItem<Material>("NPCMat");
    resoursmanager.IncludeItem<Material>("RoadMat");

    resoursmanager.IncludeItem<TextureAtlas>("CharacterAtlas",char_sprite,288,360);
    AssetHandle<TextureAtlas> char_atlas_handle("CharacterAtlas");
    
    resoursmanager.IncludeItem<TextureAtlas>("EnviormentAtlas",enviorment_sprite,185,162);
    AssetHandle<TextureAtlas> enviorment_atlas_handle("EnviormentAtlas");

    auto char_atlas = resoursmanager.GetItem<TextureAtlas>("CharacterAtlas");
    char_atlas->AddRegion("PlayerWalk_Up00",       64.0f,280.0f,16.0f,20.0f);
    char_atlas->AddRegion("PlayerWalk_Up01",       64.0f,300.0f,16.0f,20.0f);
    char_atlas->AddRegion("PlayerWalk_Up02",       64.0f,320.0f,16.0f,20.0f);
    char_atlas->AddRegion("PlayerWalk_Up03",       64.0f,340.0f,16.0f,20.0f);

    char_atlas->AddRegion("PlayerWalk_Down00",     64.0f,240.0f,16.0f,20.0f);
    char_atlas->AddRegion("PlayerWalk_Down01",     64.0f,220.0f,16.0f,20.0f);
    char_atlas->AddRegion("PlayerWalk_Down02",     64.0f,200.0f,16.0f,20.0f);
    char_atlas->AddRegion("PlayerWalk_Down03",     64.0f,180.0f,16.0f,20.0f);

    char_atlas->AddRegion("PlayerWalk_Right00",    80.0f, 260.0f,16.0f,20.0f);
    char_atlas->AddRegion("PlayerWalk_Right01",    96.0f, 260.0f,16.0f,20.0f);
    char_atlas->AddRegion("PlayerWalk_Right02",    112.0f,260.0f,16.0f,20.0f);
    char_atlas->AddRegion("PlayerWalk_Right03",    128.0f,260.0f,16.0f,20.0f);

    char_atlas->AddRegion("PlayerWalk_Left00",     48.0f,260.0f,16.0f,20.0f);
    char_atlas->AddRegion("PlayerWalk_Left01",     32.0f,260.0f,16.0f,20.0f);
    char_atlas->AddRegion("PlayerWalk_Left02",     16.0f,260.0f,16.0f,20.0f);
    char_atlas->AddRegion("PlayerWalk_Left03",     0.0f, 260.0f,16.0f,20.0f);

    char_atlas->AddRegion("PlayerWalk_UpRight00",  80.0f, 280.0f,16.0f,20.0f);
    char_atlas->AddRegion("PlayerWalk_UpRight01",  96.0f, 300.0f,16.0f,20.0f);
    char_atlas->AddRegion("PlayerWalk_UpRight02",  112.0f,320.0f,16.0f,20.0f);
    char_atlas->AddRegion("PlayerWalk_UpRight03",  128.0f,340.0f,16.0f,20.0f);

    char_atlas->AddRegion("PlayerWalk_DownRight00",80.0f, 240.0f,16.0f,20.0f);
    char_atlas->AddRegion("PlayerWalk_DownRight01",96.0f, 220.0f,16.0f,20.0f);
    char_atlas->AddRegion("PlayerWalk_DownRight02",112.0f,200.0f,16.0f,20.0f);
    char_atlas->AddRegion("PlayerWalk_DownRight03",128.0f,180.0f,16.0f,20.0f);

    char_atlas->AddRegion("PlayerWalk_DownLeft00", 48.0f,240.0f,16.0f,20.0f);
    char_atlas->AddRegion("PlayerWalk_DownLeft01", 32.0f,220.0f,16.0f,20.0f);
    char_atlas->AddRegion("PlayerWalk_DownLeft02", 16.0f,200.0f,16.0f,20.0f);
    char_atlas->AddRegion("PlayerWalk_DownLeft03", 0.0f, 180.0f,16.0f,20.0f);

    char_atlas->AddRegion("PlayerWalk_UpLeft00",   48.0f,280.0f,16.0f,20.0f);
    char_atlas->AddRegion("PlayerWalk_UpLeft01",   32.0f,300.0f,16.0f,20.0f);
    char_atlas->AddRegion("PlayerWalk_UpLeft02",   16.0f,320.0f,16.0f,20.0f);
    char_atlas->AddRegion("PlayerWalk_UpLeft03",   0.0f, 340.0f,16.0f,20.0f);
    std::vector<std::string> redwalk_down_vec=  {"PlayerWalk_Down00",  "PlayerWalk_Down01",   "PlayerWalk_Down02",   "PlayerWalk_Down03"};
    std::vector<std::string> redwalk_right_vec= {"PlayerWalk_Right00", "PlayerWalk_Right01",  "PlayerWalk_Right02",  "PlayerWalk_Right03"};
    std::vector<std::string> redwalk_up_vec=    {"PlayerWalk_Up00",    "PlayerWalk_Up01",     "PlayerWalk_Up02",     "PlayerWalk_Up03"};
    std::vector<std::string> redwalk_left_vec=  {"PlayerWalk_Left00",  "PlayerWalk_Left01",   "PlayerWalk_Left02",   "PlayerWalk_Left03"};
    std::vector<std::string> redwalk_downright_vec ={"PlayerWalk_DownRight00",   "PlayerWalk_DownRight01", "PlayerWalk_DownRight02", "PlayerWalk_DownRight03"};
    std::vector<std::string> redwalk_upright_vec   ={"PlayerWalk_UpRight00",     "PlayerWalk_UpRight01",   "PlayerWalk_UpRight02",   "PlayerWalk_UpRight03"};
    std::vector<std::string> redwalk_upleft_vec    ={"PlayerWalk_UpLeft00",      "PlayerWalk_UpLeft01",    "PlayerWalk_UpLeft02",    "PlayerWalk_UpLeft03"};
    std::vector<std::string> redwalk_downleft_vec  ={"PlayerWalk_DownLeft00",    "PlayerWalk_DownLeft01",  "PlayerWalk_DownLeft02",  "PlayerWalk_DownLeft03"};
    std::vector<std::string> redidle_down_vec=  {"PlayerWalk_Down00"};
    std::vector<std::string> redidle_right_vec= {"PlayerWalk_Right00"};
    std::vector<std::string> redidle_up_vec=    {"PlayerWalk_Up00"};
    std::vector<std::string> redidle_left_vec=  {"PlayerWalk_Left00"};
    std::vector<std::string> redidle_downright_vec ={"PlayerWalk_DownRight00"};
    std::vector<std::string> redidle_upright_vec   ={"PlayerWalk_UpRight00"};
    std::vector<std::string> redidle_upleft_vec    ={"PlayerWalk_UpLeft00"};
    std::vector<std::string> redidle_downleft_vec  ={"PlayerWalk_DownLeft00"};
    
    resoursmanager.IncludeItem<Animation>("PlayerWalk_down" , redwalk_down_vec,    0.1f,1);
    resoursmanager.IncludeItem<Animation>("PlayerWalk_right", redwalk_right_vec,   0.1f,1);
    resoursmanager.IncludeItem<Animation>("PlayerWalk_up"   , redwalk_up_vec,      0.1f,1);
    resoursmanager.IncludeItem<Animation>("PlayerWalk_left" , redwalk_left_vec,    0.1f,1);
    resoursmanager.IncludeItem<Animation>("PlayerWalk_downright" , redwalk_downright_vec,0.1f,1);
    resoursmanager.IncludeItem<Animation>("PlayerWalk_upright",  redwalk_upright_vec,    0.1f,1);
    resoursmanager.IncludeItem<Animation>("PlayerWalk_upleft"   , redwalk_upleft_vec,    0.1f,1);
    resoursmanager.IncludeItem<Animation>("PlayerWalk_downleft" , redwalk_downleft_vec,  0.1f,1);

    
    resoursmanager.IncludeItem<Animation>("PlayerIdle_down" ,       redidle_down_vec,    0.1f,0);
    resoursmanager.IncludeItem<Animation>("PlayerIdle_right",       redidle_right_vec,   0.1f,0);
    resoursmanager.IncludeItem<Animation>("PlayerIdle_up"   ,       redidle_up_vec,      0.1f,0);
    resoursmanager.IncludeItem<Animation>("PlayerIdle_left" ,       redidle_left_vec,    0.1f,0);
    resoursmanager.IncludeItem<Animation>("PlayerIdle_downright" ,  redidle_downright_vec,0.1f,0);
    resoursmanager.IncludeItem<Animation>("PlayerIdle_upright",     redidle_upright_vec,    0.1f,0);
    resoursmanager.IncludeItem<Animation>("PlayerIdle_upleft"   ,   redidle_upleft_vec,    0.1f,0);
    resoursmanager.IncludeItem<Animation>("PlayerIdle_downleft" ,   redidle_downleft_vec,  0.1f,0);
    AssetHandle<Animation> redwalk_up       ("PlayerWalk_up");
    AssetHandle<Animation> redwalk_down     ("PlayerWalk_down");
    AssetHandle<Animation> redwalk_right    ("PlayerWalk_right");
    AssetHandle<Animation> redwalk_left     ("PlayerWalk_left");
    AssetHandle<Animation> redwalk_upleft   ("PlayerWalk_upleft");
    AssetHandle<Animation> redwalk_downright("PlayerWalk_downright");
    AssetHandle<Animation> redwalk_upright  ("PlayerWalk_upright");
    AssetHandle<Animation> redwalk_downleft ("PlayerWalk_downleft");
    AssetHandle<Animation> redidle_up       ("PlayerIdle_up");
    AssetHandle<Animation> redidle_down     ("PlayerIdle_down");
    AssetHandle<Animation> redidle_right    ("PlayerIdle_right");
    AssetHandle<Animation> redidle_left     ("PlayerIdle_left");
    AssetHandle<Animation> redidle_upleft   ("PlayerIdle_upleft");
    AssetHandle<Animation> redidle_downright("PlayerIdle_downright");
    AssetHandle<Animation> redidle_upright  ("PlayerIdle_upright");
    AssetHandle<Animation> redidle_downleft ("PlayerIdle_downleft");


    char_atlas->AddRegion("BlackWalk_Up00",64.0f,100.0f,16.0f,20.0f);
    char_atlas->AddRegion("BlackWalk_Up01",64.0f,120.0f,16.0f,20.0f);
    char_atlas->AddRegion("BlackWalk_Up02",64.0f,140.0f,16.0f,20.0f);
    char_atlas->AddRegion("BlackWalk_Up03",64.0f,160.0f,16.0f,20.0f);

    char_atlas->AddRegion("BlackWalk_Down00",64.0f,60.0f,16.0f,20.0f);
    char_atlas->AddRegion("BlackWalk_Down01",64.0f,40.0f,16.0f,20.0f);
    char_atlas->AddRegion("BlackWalk_Down02",64.0f,20.0f,16.0f,20.0f);
    char_atlas->AddRegion("BlackWalk_Down03",64.0f,0.0f,16.0f,20.0f);

    char_atlas->AddRegion("BlackWalk_Right00",80.0f,80.0f,16.0f,20.0f);
    char_atlas->AddRegion("BlackWalk_Right01",96.0f,80.0f,16.0f,20.0f);
    char_atlas->AddRegion("BlackWalk_Right02",112.0f,80.0f,16.0f,20.0f);
    char_atlas->AddRegion("BlackWalk_Right03",128.0f,80.0f,16.0f,20.0f);

    char_atlas->AddRegion("BlackWalk_Left00",48.0f,80.0f,16.0f,20.0f);
    char_atlas->AddRegion("BlackWalk_Left01",32.0f,80.0f,16.0f,20.0f);
    char_atlas->AddRegion("BlackWalk_Left02",16.0f,80.0f,16.0f,20.0f);
    char_atlas->AddRegion("BlackWalk_Left03",0.0f,80.0f,16.0f,20.0f);

    char_atlas->AddRegion("BlackWalk_UpRight00",80.0f, 100.0f,16.0f,20.0f);
    char_atlas->AddRegion("BlackWalk_UpRight01",96.0f, 120.0f,16.0f,20.0f);
    char_atlas->AddRegion("BlackWalk_UpRight02",112.0f,140.0f,16.0f,20.0f);
    char_atlas->AddRegion("BlackWalk_UpRight03",128.0f,160.0f,16.0f,20.0f);

    char_atlas->AddRegion("BlackWalk_DownRight00",80.0f,60.0f,16.0f,20.0f);
    char_atlas->AddRegion("BlackWalk_DownRight01",96.0f,40.0f,16.0f,20.0f);
    char_atlas->AddRegion("BlackWalk_DownRight02",112.0f,20.0f,16.0f,20.0f);
    char_atlas->AddRegion("BlackWalk_DownRight03",128.0f,0.0f,16.0f,20.0f);

    char_atlas->AddRegion("BlackWalk_DownLeft00",48.0f,60.0f,16.0f,20.0f);
    char_atlas->AddRegion("BlackWalk_DownLeft01",32.0f,40.0f,16.0f,20.0f);
    char_atlas->AddRegion("BlackWalk_DownLeft02",16.0f,20.0f,16.0f,20.0f);
    char_atlas->AddRegion("BlackWalk_DownLeft03",0.0f,0.0f,16.0f,20.0f);

    char_atlas->AddRegion("BlackWalk_UpLeft00",48.0f,100.0f,16.0f,20.0f);
    char_atlas->AddRegion("BlackWalk_UpLeft01",32.0f,120.0f,16.0f,20.0f);
    char_atlas->AddRegion("BlackWalk_UpLeft02",16.0f,140.0f,16.0f,20.0f);
    char_atlas->AddRegion("BlackWalk_UpLeft03",0.0f, 160.0f,16.0f,20.0f);
    std::vector<std::string> blackwalk_down_vec ={"BlackWalk_Down00",   "BlackWalk_Down01",   "BlackWalk_Down02", "BlackWalk_Down03"};
    std::vector<std::string> blackwalk_right_vec={"BlackWalk_Right00",  "BlackWalk_Right01",  "BlackWalk_Right02","BlackWalk_Right03"};
    std::vector<std::string> blackwalk_up_vec   ={"BlackWalk_Up00",     "BlackWalk_Up01",     "BlackWalk_Up02",   "BlackWalk_Up03"};
    std::vector<std::string> blackwalk_left_vec ={"BlackWalk_Left00",   "BlackWalk_Left01",   "BlackWalk_Left02", "BlackWalk_Left03"};
    
    std::vector<std::string> blackwalk_downright_vec ={"BlackWalk_DownRight00",   "BlackWalk_DownRight01", "BlackWalk_DownRight02", "BlackWalk_DownRight03"};
    std::vector<std::string> blackwalk_upright_vec   ={"BlackWalk_UpRight00",     "BlackWalk_UpRight01",   "BlackWalk_UpRight02",   "BlackWalk_UpRight03"};
    std::vector<std::string> blackwalk_upleft_vec    ={"BlackWalk_UpLeft00",      "BlackWalk_UpLeft01",    "BlackWalk_UpLeft02",    "BlackWalk_UpLeft03"};
    std::vector<std::string> blackwalk_downleft_vec  ={"BlackWalk_DownLeft00",    "BlackWalk_DownLeft01",  "BlackWalk_DownLeft02",  "BlackWalk_DownLeft03"};
    
    
    std::vector<std::string> blackidle_down_vec=      {"BlackWalk_Down00"};
    std::vector<std::string> blackidle_right_vec=     {"BlackWalk_Right00"};
    std::vector<std::string> blackidle_up_vec=        {"BlackWalk_Up00"};
    std::vector<std::string> blackidle_left_vec=      {"BlackWalk_Left00"};
    std::vector<std::string> blackidle_downright_vec ={"BlackWalk_DownRight00"};
    std::vector<std::string> blackidle_upright_vec   ={"BlackWalk_UpRight00"};
    std::vector<std::string> blackidle_upleft_vec    ={"BlackWalk_UpLeft00"};
    std::vector<std::string> blackidle_downleft_vec  ={"BlackWalk_DownLeft00"};

    resoursmanager.IncludeItem<Animation>("BlackWalk_down" , blackwalk_down_vec,0.1f,1);
    resoursmanager.IncludeItem<Animation>("BlackWalk_right", blackwalk_right_vec,0.1f,1);
    resoursmanager.IncludeItem<Animation>("BlackWalk_up"   , blackwalk_up_vec,0.1f,1);
    resoursmanager.IncludeItem<Animation>("BlackWalk_left" , blackwalk_left_vec,0.1f,1);
    resoursmanager.IncludeItem<Animation>("BlackWalk_downright" ,blackwalk_downright_vec,0.1f,1);
    resoursmanager.IncludeItem<Animation>("BlackWalk_upright",   blackwalk_upright_vec,0.1f,1);
    resoursmanager.IncludeItem<Animation>("BlackWalk_upleft"   , blackwalk_upleft_vec,0.1f,1);
    resoursmanager.IncludeItem<Animation>("BlackWalk_downleft" , blackwalk_downleft_vec,0.1f,1);

    resoursmanager.IncludeItem<Animation>("BlackIdle_down" ,       blackidle_down_vec,    0.1f,0);
    resoursmanager.IncludeItem<Animation>("BlackIdle_right",       blackidle_right_vec,   0.1f,0);
    resoursmanager.IncludeItem<Animation>("BlackIdle_up"   ,       blackidle_up_vec,      0.1f,0);
    resoursmanager.IncludeItem<Animation>("BlackIdle_left" ,       blackidle_left_vec,    0.1f,0);
    resoursmanager.IncludeItem<Animation>("BlackIdle_downright" ,  blackidle_downright_vec,0.1f,0);
    resoursmanager.IncludeItem<Animation>("BlackIdle_upright",     blackidle_upright_vec,    0.1f,0);
    resoursmanager.IncludeItem<Animation>("BlackIdle_upleft"   ,   blackidle_upleft_vec,    0.1f,0);
    resoursmanager.IncludeItem<Animation>("BlackIdle_downleft" ,   blackidle_downleft_vec,  0.1f,0);

    AssetHandle<Animation> blackwalk_up       ("BlackWalk_up");
    AssetHandle<Animation> blackwalk_down     ("BlackWalk_down");
    AssetHandle<Animation> blackwalk_right    ("BlackWalk_right");
    AssetHandle<Animation> blackwalk_left     ("BlackWalk_left");
    AssetHandle<Animation> blackwalk_upleft   ("BlackWalk_upleft");
    AssetHandle<Animation> blackwalk_downright("BlackWalk_downright");
    AssetHandle<Animation> blackwalk_upright  ("BlackWalk_upright");
    AssetHandle<Animation> blackwalk_downleft ("BlackWalk_downleft");
    AssetHandle<Animation> blackidle_up       ("BlackIdle_up");
    AssetHandle<Animation> blackidle_down     ("BlackIdle_down");
    AssetHandle<Animation> blackidle_right    ("BlackIdle_right");
    AssetHandle<Animation> blackidle_left     ("BlackIdle_left");
    AssetHandle<Animation> blackidle_upleft   ("BlackIdle_upleft");
    AssetHandle<Animation> blackidle_downright("BlackIdle_downright");
    AssetHandle<Animation> blackidle_upright  ("BlackIdle_upright");
    AssetHandle<Animation> blackidle_downleft ("BlackIdle_downleft");


    auto enviorment_atlas = resoursmanager.Resolve(enviorment_atlas_handle);
    enviorment_atlas->AddRegion("Road1",0.0f,110.0f,111.0f,52.0f);
    enviorment_atlas->AddRegion("Road2",0.0f,408.0f,111.0f,52.0f);
    enviorment_atlas->AddRegion("Tree1",112.0f,440.0f,33.0f,72.0f);
    enviorment_atlas->AddRegion("Tree1",149.0f,440.0f,33.0f,72.0f);
    enviorment_atlas->AddRegion("Car",1.0f,348.0f,171.0f,60.0f);


    resoursmanager.GetItem<Material>("PlayerMat")->SetShader(sprite_shader_with_normal);
    resoursmanager.GetItem<Material>("PlayerMat")->SetTexture(char_sprite);
    resoursmanager.GetItem<Material>("PlayerMat")->SetNormal(char_normal);
    
    resoursmanager.GetItem<Material>("NPCMat")->SetShader(sprite_shader_with_normal);
    resoursmanager.GetItem<Material>("NPCMat")->SetTexture(char_sprite);
    resoursmanager.GetItem<Material>("NPCMat")->SetNormal(char_normal);
    
    resoursmanager.GetItem<Material>("RoadMat")->SetShader(sprite_shader_without_normal);
    resoursmanager.GetItem<Material>("RoadMat")->SetTexture(enviorment_sprite);
    

    AssetHandle<Material> player_material("PlayerMat");
    AssetHandle<Material> npc_material   ("NPCMat");
    AssetHandle<Material> road_material  ("RoadMat");

    Scene scene("Sahne1");
    scene.Activate();
    scene.Init();

    uint64_t yol1ID = scene.AddEntity("YOL");
    uint64_t yol2ID = scene.AddEntity("YOL");
    uint64_t yol3ID = scene.AddEntity("YOL");
    uint64_t npc1ID = scene.AddEntity("NPC");
    uint64_t playerID = scene.AddEntity("Player");
    uint64_t cameraID = scene.AddEntity("Camera");
    uint64_t HandsID = scene.AddEntity("Hands");
    uint64_t light1ID = scene.AddEntity("Light1");
    uint64_t AmbientlightID = scene.AddEntity("AmbientLight");

    scene.FindEntity(light1ID)->AddComponent<TransformComp>();
    scene.FindEntity(light1ID)->AddComponent<LightComponent>(glm::vec4(1.0f),1000.0f);
    scene.FindEntity(light1ID)->init();

    scene.FindEntity(AmbientlightID)->AddComponent<TransformComp>();
    scene.FindEntity(AmbientlightID)->AddComponent<AmbientLightComponent>(glm::vec4(0.4f, 0.4f, 0.4f, 1.0f));
    scene.FindEntity(AmbientlightID)->init();

    scene.FindEntity(npc1ID)->AddComponent<TransformComp>();
    scene.FindEntity(npc1ID)->AddComponent<MaterialComponent>(npc_material);
    scene.FindEntity(npc1ID)->AddComponent<RendererComponent>(2,1.0f);
    scene.FindEntity(npc1ID)->AddComponent<SpriteComponent>(char_atlas_handle,"BlackWalk_Down00");
    scene.FindEntity(npc1ID)->AddComponent<AnimationComponent>()->AddOwner(scene.FindEntity(npc1ID));
    scene.FindEntity(npc1ID)->AddComponent<ScriptComponent>(std::make_unique<TestScript2>());
    scene.FindEntity(npc1ID)->GetComponent<ScriptComponent>()->SetEntity(scene.FindEntity(npc1ID));
    scene.FindEntity(npc1ID)->init();

    scene.FindEntity(yol1ID)->AddComponent<TransformComp>();
    scene.FindEntity(yol1ID)->AddComponent<MaterialComponent>(road_material);
    scene.FindEntity(yol1ID)->AddComponent<RendererComponent>(1,0.0f);
    scene.FindEntity(yol1ID)->AddComponent<SpriteComponent>(enviorment_atlas_handle,"Road1");
    scene.FindEntity(yol1ID)->init();

    scene.FindEntity(yol2ID)->AddComponent<TransformComp>();
    scene.FindEntity(yol2ID)->AddComponent<MaterialComponent>(road_material);
    scene.FindEntity(yol2ID)->AddComponent<RendererComponent>(1,1.0f);
    scene.FindEntity(yol2ID)->AddComponent<SpriteComponent>(enviorment_atlas_handle,"Road1");
    scene.FindEntity(yol2ID)->init();

    scene.FindEntity(yol3ID)->AddComponent<TransformComp>();
    scene.FindEntity(yol3ID)->AddComponent<MaterialComponent>(road_material);
    scene.FindEntity(yol3ID)->AddComponent<RendererComponent>(1,2.0f);
    scene.FindEntity(yol3ID)->AddComponent<SpriteComponent>(enviorment_atlas_handle,"Road1");
    scene.FindEntity(yol3ID)->init();

    scene.FindEntity(playerID)->AddComponent<TransformComp>();
    scene.FindEntity(playerID)->AddComponent<MaterialComponent>(player_material);
    scene.FindEntity(playerID)->AddComponent<ScriptComponent>(std::make_unique<PlayerScript>());
    scene.FindEntity(playerID)->GetComponent<ScriptComponent>()->SetEntity(scene.FindEntity(playerID));
    scene.FindEntity(playerID)->GetComponent<ScriptComponent>()->SetInput(&input);
    scene.FindEntity(playerID)->AddComponent<RendererComponent>(2,2.0f);
    scene.FindEntity(playerID)->AddComponent<SpriteComponent>(char_atlas_handle,"PlayerWalk_Down00");
    scene.FindEntity(playerID)->AddComponent<AnimationComponent>()->AddOwner(scene.FindEntity(playerID));
    scene.FindEntity(playerID)->init();
    
    scene.FindEntity(cameraID)->AddComponent<ScriptComponent>(std::make_unique<CameraScript>());
    scene.FindEntity(cameraID)->GetComponent<ScriptComponent>()->GetScript<CameraScript>()->SetCamera(&camera);
    scene.FindEntity(cameraID)->GetComponent<ScriptComponent>()->GetScript<CameraScript>()->SetCameraEntity(scene.FindEntity(cameraID));
    scene.FindEntity(cameraID)->GetComponent<ScriptComponent>()->GetScript<CameraScript>()->SetTarget(scene.FindEntity(playerID));
    scene.FindEntity(cameraID)->GetComponent<ScriptComponent>()->SetInput(&input);
    scene.FindEntity(cameraID)->init();


    scene.FindEntity(HandsID)->AddComponent<ScriptComponent>(std::make_unique<HandsScript>());
    scene.FindEntity(HandsID)->init();
    
    Entity* Hands = scene.FindEntity(HandsID);
    TransformComp* transformcomponent;
    AnimationComponent* animationcomp = scene.FindEntity(playerID)->GetComponent<AnimationComponent>();
    animationcomp->AddAnimation("PlayerWalk_Up",      redwalk_up);
    animationcomp->AddAnimation("PlayerWalk_Down",    redwalk_down);
    animationcomp->AddAnimation("PlayerWalk_Right",   redwalk_right);
    animationcomp->AddAnimation("PlayerWalk_Left",    redwalk_left);
    animationcomp->AddAnimation("PlayerWalk_UpLeft",      redwalk_upleft);
    animationcomp->AddAnimation("PlayerWalk_DownLeft",    redwalk_downleft);
    animationcomp->AddAnimation("PlayerWalk_UpRight",     redwalk_upright);
    animationcomp->AddAnimation("PlayerWalk_DownRight",   redwalk_downright);
    animationcomp->AddAnimation("PlayerIdle_Up",      redidle_up);
    animationcomp->AddAnimation("PlayerIdle_Down",    redidle_down);
    animationcomp->AddAnimation("PlayerIdle_Right",   redidle_right);
    animationcomp->AddAnimation("PlayerIdle_Left",    redidle_left);
    animationcomp->AddAnimation("PlayerIdle_UpLeft",      redidle_upleft);
    animationcomp->AddAnimation("PlayerIdle_DownLeft",    redidle_downleft);
    animationcomp->AddAnimation("PlayerIdle_UpRight",     redidle_upright);
    animationcomp->AddAnimation("PlayerIdle_DownRight",   redidle_downright);

    animationcomp = scene.FindEntity(npc1ID)->GetComponent<AnimationComponent>();
    animationcomp->AddAnimation("BlackWalk_Up",      blackwalk_up);
    animationcomp->AddAnimation("BlackWalk_Down",    blackwalk_down);
    animationcomp->AddAnimation("BlackWalk_Right",   blackwalk_right);
    animationcomp->AddAnimation("BlackWalk_Left",    blackwalk_left);
    animationcomp->AddAnimation("BlackWalk_UpLeft",      blackwalk_upleft);
    animationcomp->AddAnimation("BlackWalk_DownLeft",    blackwalk_downleft);
    animationcomp->AddAnimation("BlackWalk_UpRight",     blackwalk_upright);
    animationcomp->AddAnimation("BlackWalk_DownRight",   blackwalk_downright);
    animationcomp->AddAnimation("BlackIdle_Up",      blackidle_up);
    animationcomp->AddAnimation("BlackIdle_Down",    blackidle_down);
    animationcomp->AddAnimation("BlackIdle_Right",   blackidle_right);
    animationcomp->AddAnimation("BlackIdle_Left",    blackidle_left);
    animationcomp->AddAnimation("BlackIdle_UpLeft",      blackidle_upleft);
    animationcomp->AddAnimation("BlackIdle_DownLeft",    blackidle_downleft);
    animationcomp->AddAnimation("BlackIdle_UpRight",     blackidle_upright);
    animationcomp->AddAnimation("BlackIdle_DownRight",   blackidle_downright);

    transformcomponent = scene.FindEntity(light1ID)->GetComponent<TransformComp>();
    transformcomponent->position = glm::vec2(npc_x,npc_y);

    transformcomponent = scene.FindEntity(npc1ID)->GetComponent<TransformComp>();
    transformcomponent->position = glm::vec2(300.0f,200.0f);
    transformcomponent->rotation = 0.0f;
    transformcomponent->scale = glm::vec2(10.0f,12.5f);

    transformcomponent = scene.FindEntity(yol1ID)->GetComponent<TransformComp>();
    transformcomponent->position = glm::vec2(0.0f,0.0f);
    transformcomponent->rotation = 0.0f;
    transformcomponent->scale = glm::vec2(12.0f,10.0f);

    transformcomponent = scene.FindEntity(yol2ID)->GetComponent<TransformComp>();
    transformcomponent->position = glm::vec2(1483.0f,0.0f);
    transformcomponent->rotation = 0.0f;
    transformcomponent->scale = glm::vec2(12.0f,10.0f);

    transformcomponent = scene.FindEntity(yol3ID)->GetComponent<TransformComp>();
    transformcomponent->position = glm::vec2(2966.0f,0.0f);
    transformcomponent->rotation = 0.0f;
    transformcomponent->scale = glm::vec2(12.0f,10.0f);

    transformcomponent = scene.FindEntity(playerID)->GetComponent<TransformComp>();
    transformcomponent->position = glm::vec2(npc_x,npc_y);
    transformcomponent->rotation = 0.0f;
    transformcomponent->scale = glm::vec2(10.0f,12.5f);
    
    camera.SetWorldSize(100000.0f, 100000.0f, 50000.0f, -50000.0f, 50000.0f, -50000.0f);
    Renderer renderer(camera,window.GetWidth(),window.GetHeight(),vertexShaderSource_postprocesser.c_str(),fragmentShaderSource_postprocesser.c_str());

    window.SetEventCallBack([&renderer,&window,&npc_x,&npc_y,&scene,&resoursmanager,&playerID,&cameraID,&camera](Event& event){ 
        scene.OnEvent(event);
        EventDispatcher dispatcher(event);
        dispatcher.Dispatcher<WindowResizeEvent>(
            [&renderer,&window](WindowResizeEvent& event)
            {
                int w =event.GetWidth();
                int h =event.GetHeight();
                // std::cout << "Resize: " <<w <<","<<h <<"\n";
                glViewport(0,0,w,h);
                renderer.SetProjection(w,h);
                window.WindowResize(w,h);
            }
        );
        dispatcher.Dispatcher<KeyPressedEvent>(
            [&camera,&resoursmanager,&scene,&playerID](KeyPressedEvent& event)
            {
                // std::cout << "Key pressed: "<<event.GetKey() <<"\n";
                if(event.GetKey()==GLFW_KEY_SPACE) scene.FindEntity(playerID)->GetComponent<AnimationComponent>()->Reset();
                if(event.GetKey()==GLFW_KEY_O){
                    camera.Shake(15.0f,0.2f);
                }
                if(event.GetKey()==GLFW_KEY_K){
                    camera.Shake(20.0f,0.2f);
                }
                if(event.GetKey()==GLFW_KEY_L){
                    camera.Shake(30.0f,0.2f);
                }
            }
        );
        dispatcher.Dispatcher<MousePressedEvent>(
            [&camera](MousePressedEvent& event)
            {
                // std::cout << "Key pressed: "<<event.GetButton() <<"\n";
            }
        );
        dispatcher.Dispatcher<CursorMoveEvent>(
            [&camera,&scene,&playerID](CursorMoveEvent& event)
            {
                // glm::vec2 world = camera.ScreentoWorld(event.GetXPos(), event.GetYPos());
                // std::cout << "ScreenX/Y: " << event.GetXPos() << "," << event.GetYPos() << "\n";
                // std::cout << "resW/resH: " << camera.GetResW() << "," << camera.GetResH() << "\n";
                // std::cout << "width/height (world): " << camera.GetWidth() << "," << camera.GetHeight() << "\n";
                // std::cout << "zoom: " << camera.GetZoom() << "\n";
                // std::cout << "CameraPos: " << camera.GetPosition().x << "," << camera.GetPosition().y << "\n";
                // std::cout << "World: " << world.x << "," << world.y << "\n\n";
                // glm::vec2 screen = camera.WorldToScreen(scene.FindEntity(playerID)->GetComponent<TransformComp>()->position.x,scene.FindEntity(playerID)->GetComponent<TransformComp>()->position.y);
                // std::cout << "\t---\t---\t---\nresW/resH: " << event.GetXPos() << "," << event.GetYPos() << "\n";
                // std::cout << "Screen: " << screen.x << "," << screen.y << "\n\n";

            }
        );
        dispatcher.Dispatcher<ScrollEvent>(
            [](ScrollEvent& event)
            {
                // std::cout << "Scroll Offsets: "<<event.GetXOffset() <<","<<event.GetYOffset() <<"\n";
            }
        );
    });





    while(window.windowrunning()){
        
        time.Update();
        std::cout<<"FPS: "<< 1/time.GetDeltaTime()<<"\n";
        window.PollEvents();
        input.Update();
        window.clear();
        camera.Update(time.GetDeltaTime());
        scene.Update(time.GetDeltaTime());
        scene.AnimationUpdate(time.GetDeltaTime(),&resoursmanager);
        renderer.Draw(scene,resoursmanager);
        window.SwapBuffer();

    }
    return 0;
}