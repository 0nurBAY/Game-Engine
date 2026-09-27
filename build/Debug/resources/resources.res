#textures
TEXTURE CharacterSprite assets/char_sprites.png
TEXTURE EnviormentSprite assets/enviorment_sprite2.png

TEXTURE CharacterNormal assets/char_sprite_normal.png
TEXTURE EnviormentNormal assets/enviorment_sprite_normal.png


#shaders
SHADER ShaderWithNormal shaders/sprite.vert shaders/sprite01.frag
SHADER ShaderWithOutNormal shaders/sprite.vert shaders/sprite00.frag


#texture atlases
TEXTUREATLAS CharacterAtlas CharacterSprite 288 360

ATLAS_ADD CharacterAtlas PlayerWalk_Up00 64.0 280.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerWalk_Up01 64.0 300.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerWalk_Up02 64.0 320.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerWalk_Up03 64.0 340.0 16.0 20.0

ATLAS_ADD CharacterAtlas PlayerWalk_Down00 64.0 240.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerWalk_Down01 64.0 220.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerWalk_Down02 64.0 200.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerWalk_Down03 64.0 180.0 16.0 20.0

ATLAS_ADD CharacterAtlas PlayerWalk_Right00 80.0 260.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerWalk_Right01 96.0 260.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerWalk_Right02 112.0 260.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerWalk_Right03 128.0 260.0 16.0 20.0

ATLAS_ADD CharacterAtlas PlayerWalk_Left00 48.0 260.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerWalk_Left01 32.0 260.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerWalk_Left02 16.0 260.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerWalk_Left03 0.0 260.0 16.0 20.0

ATLAS_ADD CharacterAtlas PlayerWalk_UpRight00 80.0 280.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerWalk_UpRight01 96.0 300.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerWalk_UpRight02 112.0 320.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerWalk_UpRight03 128.0 340.0 16.0 20.0

ATLAS_ADD CharacterAtlas PlayerWalk_DownRight00 80.0 240.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerWalk_DownRight01 96.0 220.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerWalk_DownRight02 112.0 200.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerWalk_DownRight03 128.0 180.0 16.0 20.0

ATLAS_ADD CharacterAtlas PlayerWalk_DownLeft00 48.0 240.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerWalk_DownLeft01 32.0 220.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerWalk_DownLeft02 16.0 200.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerWalk_DownLeft03 0.0 180.0 16.0 20.0

ATLAS_ADD CharacterAtlas PlayerWalk_UpLeft00 48.0 280.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerWalk_UpLeft01 32.0 300.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerWalk_UpLeft02 16.0 320.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerWalk_UpLeft03 0.0 340.0 16.0 20.0

ATLAS_ADD CharacterAtlas PlayerHold_Down00 80.0 220.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerHold_Down01 80.0 200.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerHold_Down02 80.0 220.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerHold_Down03 80.0 180.0 16.0 20.0
#-------------------------------------------------------------
ATLAS_ADD CharacterAtlas PlayerAttack_Down00 96.0 200.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerAttack_Down01 96.0 180.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerAttack_Down02 112.0 180.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerAttack_Down03 96.0 180.0 16.0 20.0

ATLAS_ADD CharacterAtlas PlayerAttack_DownRight00 96.0 240.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerAttack_DownRight01 112.0 240.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerAttack_DownRight02 128.0 240.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerAttack_DownRight03 112.0 240.0 16.0 20.0

ATLAS_ADD CharacterAtlas PlayerAttack_Right00 112.0 300.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerAttack_Right01 128.0 300.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerAttack_Right02 128.0 320.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerAttack_Right03 128.0 300.0 16.0 20.0

ATLAS_ADD CharacterAtlas PlayerAttack_UpRight00 80.0 300.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerAttack_UpRight01 80.0 320.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerAttack_UpRight02 80.0 340.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerAttack_UpRight03 80.0 320.0 16.0 20.0

ATLAS_ADD CharacterAtlas PlayerAttack_Up00 32.0 320.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerAttack_Up01 32.0 340.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerAttack_Up02 16.0 340.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerAttack_Up03 32.0 340.0 16.0 20.0

ATLAS_ADD CharacterAtlas PlayerAttack_UpLeft00 32.0 280.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerAttack_UpLeft01 16.0 280.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerAttack_UpLeft02 0.0 280.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerAttack_UpLeft03 16.0 280.0 16.0 20.0

ATLAS_ADD CharacterAtlas PlayerAttack_Left00 16.0 220.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerAttack_Left01 0.0 220.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerAttack_Left02 0.0 200.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerAttack_Left03 0.0 220.0 16.0 20.0

ATLAS_ADD CharacterAtlas PlayerAttack_DownLeft00 48.0 220.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerAttack_DownLeft01 48.0 200.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerAttack_DownLeft02 48.0 180.0 16.0 20.0
ATLAS_ADD CharacterAtlas PlayerAttack_DownLeft03 48.0 200.0 16.0 20.0

#NPC frames
ATLAS_ADD CharacterAtlas BlackWalk_Up00 64.0 100.0 16.0 20.0
ATLAS_ADD CharacterAtlas BlackWalk_Up01 64.0 120.0 16.0 20.0
ATLAS_ADD CharacterAtlas BlackWalk_Up02 64.0 140.0 16.0 20.0
ATLAS_ADD CharacterAtlas BlackWalk_Up03 64.0 160.0 16.0 20.0

ATLAS_ADD CharacterAtlas BlackWalk_Down00 64.0 60.0 16.0 20.0
ATLAS_ADD CharacterAtlas BlackWalk_Down01 64.0 40.0 16.0 20.0
ATLAS_ADD CharacterAtlas BlackWalk_Down02 64.0 20.0 16.0 20.0
ATLAS_ADD CharacterAtlas BlackWalk_Down03 64.0 0.0 16.0 20.0

ATLAS_ADD CharacterAtlas BlackWalk_Right00 80.0 80.0 16.0 20.0
ATLAS_ADD CharacterAtlas BlackWalk_Right01 96.0 80.0 16.0 20.0
ATLAS_ADD CharacterAtlas BlackWalk_Right02 112.0 80.0 16.0 20.0
ATLAS_ADD CharacterAtlas BlackWalk_Right03 128.0 80.0 16.0 20.0

ATLAS_ADD CharacterAtlas BlackWalk_Left00 48.0 80.0 16.0 20.0
ATLAS_ADD CharacterAtlas BlackWalk_Left01 32.0 80.0 16.0 20.0
ATLAS_ADD CharacterAtlas BlackWalk_Left02 16.0 80.0 16.0 20.0
ATLAS_ADD CharacterAtlas BlackWalk_Left03 0.0 80.0 16.0 20.0

ATLAS_ADD CharacterAtlas BlackWalk_UpRight00 80.0 100.0 16.0 20.0
ATLAS_ADD CharacterAtlas BlackWalk_UpRight01 96.0 120.0 16.0 20.0
ATLAS_ADD CharacterAtlas BlackWalk_UpRight02 112.0 140.0 16.0 20.0
ATLAS_ADD CharacterAtlas BlackWalk_UpRight03 128.0 160.0 16.0 20.0

ATLAS_ADD CharacterAtlas BlackWalk_DownRight00 80.0 60.0 16.0 20.0
ATLAS_ADD CharacterAtlas BlackWalk_DownRight01 96.0 40.0 16.0 20.0
ATLAS_ADD CharacterAtlas BlackWalk_DownRight02 112.0 20.0 16.0 20.0
ATLAS_ADD CharacterAtlas BlackWalk_DownRight03 128.0 0.0 16.0 20.0

ATLAS_ADD CharacterAtlas BlackWalk_DownLeft00 48.0 60.0 16.0 20.0
ATLAS_ADD CharacterAtlas BlackWalk_DownLeft01 32.0 40.0 16.0 20.0
ATLAS_ADD CharacterAtlas BlackWalk_DownLeft02 16.0 20.0 16.0 20.0
ATLAS_ADD CharacterAtlas BlackWalk_DownLeft03 0.0 0.0 16.0 20.0

ATLAS_ADD CharacterAtlas BlackWalk_UpLeft00 48.0 100.0 16.0 20.0
ATLAS_ADD CharacterAtlas BlackWalk_UpLeft01 32.0 120.0 16.0 20.0
ATLAS_ADD CharacterAtlas BlackWalk_UpLeft02 16.0 140.0 16.0 20.0
ATLAS_ADD CharacterAtlas BlackWalk_UpLeft03 0.0 160.0 16.0 20.0

ATLAS_ADD CharacterAtlas BlackHold_Down00 80.0 40.0 16.0 20.0
ATLAS_ADD CharacterAtlas BlackHold_Down01 80.0 20.0 16.0 20.0
ATLAS_ADD CharacterAtlas BlackHold_Down02 80.0 40.0 16.0 20.0
ATLAS_ADD CharacterAtlas BlackHold_Down03 80.0 0.0 16.0 20.0


TEXTUREATLAS EnviormentAtlas EnviormentSprite 185 162

ATLAS_ADD EnviormentAtlas Road1 0.0 110.0 111.0 52.0
ATLAS_ADD EnviormentAtlas Road2 0.0 408.0 111.0 52.0
ATLAS_ADD EnviormentAtlas Tree1 112.0 440.0 33.0 72.0
ATLAS_ADD EnviormentAtlas Tree2 149.0 440.0 33.0 72.0
ATLAS_ADD EnviormentAtlas Car 1.0 348.0 171.0 60.0


#materials
MATERIAL PlayerMat
MATERIAL_ADD TEXTURE PlayerMat CharacterSprite
MATERIAL_ADD NORMAL PlayerMat CharacterNormal
MATERIAL_ADD SHADER PlayerMat ShaderWithNormal

MATERIAL NPCMat
MATERIAL_ADD TEXTURE NPCMat CharacterSprite
MATERIAL_ADD NORMAL NPCMat CharacterNormal
MATERIAL_ADD SHADER NPCMat ShaderWithNormal

MATERIAL RoadMat
MATERIAL_ADD TEXTURE RoadMat EnviormentSprite
MATERIAL_ADD SHADER RoadMat ShaderWithOutNormal


#player animations
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

ANIMATION PlayerHold_down 0.1 loop PlayerHold_Down00 PlayerHold_Down01 PlayerHold_Down02 PlayerHold_Down03

ANIMATION PlayerAttack_down 0.1 loop PlayerAttack_Down00 PlayerAttack_Down01 PlayerAttack_Down02 PlayerAttack_Down03
ANIMATION PlayerAttack_right 0.1 loop PlayerAttack_Right00 PlayerAttack_Right01 PlayerAttack_Right02 PlayerAttack_Right03
ANIMATION PlayerAttack_up 0.1 loop PlayerAttack_Up00 PlayerAttack_Up01 PlayerAttack_Up02 PlayerAttack_Up03
ANIMATION PlayerAttack_left 0.1 loop PlayerAttack_Left00 PlayerAttack_Left01 PlayerAttack_Left02 PlayerAttack_Left03

ANIMATION PlayerAttack_downright 0.1 loop PlayerAttack_DownRight00 PlayerAttack_DownRight01 PlayerAttack_DownRight02 PlayerAttack_DownRight03
ANIMATION PlayerAttack_upright 0.1 loop PlayerAttack_UpRight00 PlayerAttack_UpRight01 PlayerAttack_UpRight02 PlayerAttack_UpRight03
ANIMATION PlayerAttack_upleft 0.1 loop PlayerAttack_UpLeft00 PlayerAttack_UpLeft01 PlayerAttack_UpLeft02 PlayerAttack_UpLeft03
ANIMATION PlayerAttack_downleft 0.1 loop PlayerAttack_DownLeft00 PlayerAttack_DownLeft01 PlayerAttack_DownLeft02 PlayerAttack_DownLeft03

#NPC animations
ANIMATION BlackWalk_down 0.1 loop BlackWalk_Down00 BlackWalk_Down01 BlackWalk_Down02 BlackWalk_Down03
ANIMATION BlackWalk_right 0.1 loop BlackWalk_Right00 BlackWalk_Right01 BlackWalk_Right02 BlackWalk_Right03
ANIMATION BlackWalk_up 0.1 loop BlackWalk_Up00 BlackWalk_Up01 BlackWalk_Up02 BlackWalk_Up03
ANIMATION BlackWalk_left 0.1 loop BlackWalk_Left00 BlackWalk_Left01 BlackWalk_Left02 BlackWalk_Left03

ANIMATION BlackWalk_downright 0.1 loop BlackWalk_DownRight00 BlackWalk_DownRight01 BlackWalk_DownRight02 BlackWalk_DownRight03
ANIMATION BlackWalk_upright 0.1 loop BlackWalk_UpRight00 BlackWalk_UpRight01 BlackWalk_UpRight02 BlackWalk_UpRight03
ANIMATION BlackWalk_upleft 0.1 loop BlackWalk_UpLeft00 BlackWalk_UpLeft01 BlackWalk_UpLeft02 BlackWalk_UpLeft03
ANIMATION BlackWalk_downleft 0.1 loop BlackWalk_DownLeft00 BlackWalk_DownLeft01 BlackWalk_DownLeft02 BlackWalk_DownLeft03

ANIMATION BlackIdle_down 0.1 once BlackWalk_Down00
ANIMATION BlackIdle_right 0.1 once BlackWalk_Right00
ANIMATION BlackIdle_up 0.1 once BlackWalk_Up00
ANIMATION BlackIdle_left 0.1 once BlackWalk_Left00

ANIMATION BlackIdle_downright 0.1 once BlackWalk_DownRight00
ANIMATION BlackIdle_upright 0.1 once BlackWalk_UpRight00
ANIMATION BlackIdle_upleft 0.1 once BlackWalk_UpLeft00
ANIMATION BlackIdle_downleft 0.1 once BlackWalk_DownLeft00

ANIMATION BlackHold_down 0.1 loop BlackHold_Down00 BlackHold_Down01 BlackHold_Down02 BlackHold_Down03
