#pragma once
//  ---------------------------------------------------------
//  CollisionComponentBullet [collision_component_bullet.h]
//                                  Author: Yuta Yanagisawa
//                                  Date  : 2022/11/21
//  ------------------------summary--------------------------
//  - �o���b�g�ƃG�l�~�[�̓����蔻��
//  - �G�l�~�[���C���[���w�肵�āA�G�l�~�[���擾
//  ---------------------------------------------------------
#include "collision_component.h"

class CollisionComponent_Bullet :
    public CollisionComponent
{
public:    
    virtual void Update() override;

    std::vector<GameObject*> IsCollisionCube_Enemy(const int& Layer);
};

