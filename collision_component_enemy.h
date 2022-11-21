#pragma once
#include "collision_component.h"

class Cylinder;
class CollisionComponent_Enemy :
    public CollisionComponent
{
public:
    virtual void Update() override;
private:
    std::vector<Cylinder*> IsCollisionCylinder();   
};

