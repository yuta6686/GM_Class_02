#pragma once
//  ---------------------------------------------------------
//  CollisionComponentEnemy [collision_component_enemy]
//                                  Author: 柳澤　優太
//                                  Date  : 2022/11/21
//  ------------------------summary--------------------------
//  - エネミーが誰かに衝突するときの処理
//  ---------------------------------------------------------
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

