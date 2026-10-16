//CollisionSolver.h

#pragma once
#include "Physics/Physictypes.h"

class CollisionSolver{
private:

public:
    static void Solve(ColliderResult* collision,bool reverse);
};
