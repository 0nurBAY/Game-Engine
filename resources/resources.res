#textures
TEXTURE CharacterSprite assets/char_sprites.png
TEXTURE EnviormentSprite assets/enviorment_sprite2.png

TEXTURE CharacterSpriteNormal assets/char_sprite_normal.png
TEXTURE EnviormentSpriteNormal assets/enviorment_sprite_normal.png

#shaders
SHADER ShaderWithNormal shaders/sprite.vert shaders/sprite00.frag
SHADER ShaderWithOutNormal shaders/sprite.vert shaders/sprite01.frag

#texture atlases
TEXTUREATLAS CharAtlas CharacterSprite 288 360
ATLAS_ADD CharAtlas PlayerWalk_Up00 64.0 280.0 16.0 20.0
ATLAS_ADD CharAtlas PlayerWalk_Up01 64.0 300.0 16.0 20.0
ATLAS_ADD CharAtlas PlayerWalk_Up02 64.0 320.0 16.0 20.0
ATLAS_ADD CharAtlas PlayerWalk_Up03 64.0 340.0 16.0 20.0

ATLAS_ADD CharAtlas PlayerWalk_Down00 64.0 240.0 16.0 20.0
ATLAS_ADD CharAtlas PlayerWalk_Down01 64.0 220.0 16.0 20.0
ATLAS_ADD CharAtlas PlayerWalk_Down02 64.0 200.0 16.0 20.0
ATLAS_ADD CharAtlas PlayerWalk_Down03 64.0 180.0 16.0 20.0

ATLAS_ADD CharAtlas PlayerWalk_Right00 80.0 260.0 16.0 20.0
ATLAS_ADD CharAtlas PlayerWalk_Right01 96.0 260.0 16.0 20.0
ATLAS_ADD CharAtlas PlayerWalk_Right02 112.0 260.0 16.0 20.0
ATLAS_ADD CharAtlas PlayerWalk_Right03 128.0 260.0 16.0 20.0

ATLAS_ADD CharAtlas PlayerWalk_Left00 48.0 260.0 16.0 20.0
ATLAS_ADD CharAtlas PlayerWalk_Left01 32.0 260.0 16.0 20.0
ATLAS_ADD CharAtlas PlayerWalk_Left02 16.0 260.0 16.0 20.0
ATLAS_ADD CharAtlas PlayerWalk_Left03 0.0 260.0 16.0 20.0

ATLAS_ADD CharAtlas PlayerWalk_UpRight00 80.0 280.0 16.0 20.0
ATLAS_ADD CharAtlas PlayerWalk_UpRight01 96.0 300.0 16.0 20.0
ATLAS_ADD CharAtlas PlayerWalk_UpRight02 112.0 320.0 16.0 20.0
ATLAS_ADD CharAtlas PlayerWalk_UpRight03 128.0 340.0 16.0 20.0

ATLAS_ADD CharAtlas PlayerWalk_DownRight00 80.0 240.0 16.0 20.0
ATLAS_ADD CharAtlas PlayerWalk_DownRight01 96.0 220.0 16.0 20.0
ATLAS_ADD CharAtlas PlayerWalk_DownRight02 112.0 200.0 16.0 20.0
ATLAS_ADD CharAtlas PlayerWalk_DownRight03 128.0 180.0 16.0 20.0

ATLAS_ADD CharAtlas PlayerWalk_DownLeft00 48.0 240.0 16.0 20.0
ATLAS_ADD CharAtlas PlayerWalk_DownLeft01 32.0 220.0 16.0 20.0
ATLAS_ADD CharAtlas PlayerWalk_DownLeft02 16.0 200.0 16.0 20.0
ATLAS_ADD CharAtlas PlayerWalk_DownLeft03 0.0 180.0 16.0 20.0

ATLAS_ADD CharAtlas PlayerWalk_UpLeft00 48.0 280.0 16.0 20.0
ATLAS_ADD CharAtlas PlayerWalk_UpLeft01 32.0 300.0 16.0 20.0
ATLAS_ADD CharAtlas PlayerWalk_UpLeft02 16.0 320.0 16.0 20.0
ATLAS_ADD CharAtlas PlayerWalk_UpLeft03 0.0 340.0 16.0 20.0

TEXTUREATLAS EnviormentAtlas EnviormentSprite 185 162
ATLAS_ADD EnviormentAtlas Road1 0.0 110.0 111.0 52.0
ATLAS_ADD EnviormentAtlas Road2 0.0 408.0 111.0 52.0
ATLAS_ADD EnviormentAtlas Tree1 112.0 440.0 33.0 72.0
ATLAS_ADD EnviormentAtlas Tree2 149.0 440.0 33.0 72.0
ATLAS_ADD EnviormentAtlas Car 1.0 348.0 171.0 60.0


#materials
MATERIAL PlayerMat
MATERIAL_ADD TEXTURE PlayerMat CharacterSprite
MATERIAL_ADD NORMAL  PlayerMat CharacterSpriteNormal
MATERIAL_ADD SHADER  PlayerMat ShaderWithNormal

MATERIAL NPCMat
MATERIAL_ADD TEXTURE NPCMat CharacterSprite
MATERIAL_ADD NORMAL  NPCMat CharacterSpriteNormal
MATERIAL_ADD SHADER  NPCMat ShaderWithNormal

MATERIAL RoadMat
MATERIAL_ADD TEXTURE RoadMat EnviormentSprite
MATERIAL_ADD SHADER  RoadMat ShaderWithOutNormal

#animaton
ANIMATION PlayerWalk_down 0.1 loop PlayerWalk_Down00 PlayerWalk_Down01 PlayerWalk_Down02 PlayerWalk_Down03
ANIMATION PlayerWalk_right 0.1 loop PlayerWalk_Right00 PlayerWalk_Right01 PlayerWalk_Right02 PlayerWalk_Right03
ANIMATION PlayerWalk_up 0.1 loop PlayerWalk_Up00 PlayerWalk_Up01 PlayerWalk_Up02 PlayerWalk_Up03
ANIMATION PlayerWalk_left 0.1 loop PlayerWalk_Left00 PlayerWalk_Left01 PlayerWalk_Left02 PlayerWalk_Left03

ANIMATION PlayerWalk_downright 0.1 loop PlayerWalk_DownRight00 PlayerWalk_DownRight01 PlayerWalk_DownRight02 PlayerWalk_DownRight03
ANIMATION PlayerWalk_upright 0.1 loop PlayerWalk_UpRight00 PlayerWalk_UpRight01 PlayerWalk_UpRight02 PlayerWalk_UpRight03
ANIMATION PlayerWalk_upleft 0.1 loop PlayerWalk_UpLeft00 PlayerWalk_UpLeft01 PlayerWalk_UpLeft02 PlayerWalk_UpLeft03
ANIMATION PlayerWalk_downleft 0.1 loop PlayerWalk_DownLeft00 PlayerWalk_DownLeft01 PlayerWalk_DownLeft02 PlayerWalk_DownLeft03

ANIMATION PlayerIdle_down 0.1 once PlayerWalk_Down00
ANIMATION PlayerIdle_right 0.1 once PlayerWalk_Right00
ANIMATION PlayerIdle_up 0.1 once PlayerWalk_Up00
ANIMATION PlayerIdle_left 0.1 once PlayerWalk_Left00

ANIMATION PlayerIdle_downright 0.1 once PlayerWalk_DownRight00
ANIMATION PlayerIdle_upright 0.1 once PlayerWalk_UpRight00
ANIMATION PlayerIdle_upleft 0.1 once PlayerWalk_UpLeft00
ANIMATION PlayerIdle_downleft 0.1 once PlayerWalk_DownLeft00
