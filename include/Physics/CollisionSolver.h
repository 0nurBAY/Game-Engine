//CollisionSolver.h

#pragma once
#include "Physics/Physictypes.h"

class CollisionSolver{
private:

public:
    static void StaticVsDynamic(ColliderResult* collision,bool reverse);
};
