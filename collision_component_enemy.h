#pragma once
//  ---------------------------------------------------------
//  CollisionComponentEnemy [collision_component_enemy]
//                                  Author: ���V�@�D��
//                                  Date  : 2022/11/21
//  ------------------------summary--------------------------
//  - �G�l�~�[���N���ɏՓ˂���Ƃ��̏���
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

