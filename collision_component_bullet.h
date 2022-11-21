#pragma once
//  ---------------------------------------------------------
//  CollisionComponentBullet [collision_component_bullet.h]
//                                  Author: Yuta Yanagisawa
//                                  Date  : 2022/11/21
//  ------------------------summary--------------------------
//  - バレットとエネミーの当たり判定
//  - エネミーレイヤーを指定して、エネミーを取得
//  ---------------------------------------------------------
#include "collision_component.h"

class CollisionComponent_Bullet :
    public CollisionComponent
{
public:    
    virtual void Update() override;

    std::vector<GameObject*> IsCollisionCube_Enemy(const int& Layer);
};

