//HitBoxDebuger.h
#pragma once

#include "Renderer/DebugRenderer.h"
#include "Physics/Physictypes.h"
#include "Scene/Entity.h"

#include <glm/glm.hpp>
class HitBoxDebug
{
private:

    static void DrawBox   (ColliderShape* shape, Entity* entity,glm::vec4 color,DebugRenderer* debugrenderer);
    static void DrawCircle(ColliderShape* shape, Entity* entity,glm::vec4 color,DebugRenderer* debugrenderer);
public:
    static void DrawHitBox(ColliderShape* shape, Entity* entity,glm::vec4 color,DebugRenderer* debugrenderer);
};