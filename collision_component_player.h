#pragma once
//  ---------------------------------------------------------
//  CollisionComponent_Player [collision_component_player.h]
//                                  Author: Yuta Yanagisawa 
//                                  Date  : 2022/11/21
//  ------------------------summary--------------------------
//  - プレイヤー
//  ---------------------------------------------------------
#include "collision_component.h"

class CountComponent;
class HPComponent;
class CollisionComponent_Player :
    public CollisionComponent
{
private:    
    static const int NO_COLL_TIME = 60;

    bool m_IsCollision = true;

    /// エネミー生成モードか？　(EnemeyGenerate)
    bool m_IsGenerateMode = false;

    // why->エネミーに衝突してから,NO_COLL_TIME秒は当たり判定無しにするため    
    CountComponent* m_Count;
    
public:
    virtual void Init()override;
    virtual void Update() override;
    void DrawImgui();

    void SetIsCollision(bool flag) { m_IsCollision = flag; }
    void SetIsGenerateMode(bool flag) { m_IsGenerateMode = flag; }    
private:    
    std::vector<GameObject*> IsCollisionSphere(const int& Layer);

    void SetParticle2D(HPComponent* hp);
};

