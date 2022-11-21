#pragma once
//  ---------------------------------------------------------
//  CollisionComponent_Player [collision_component_player.h]
//                                  Author: Yuta Yanagisawa 
//                                  Date  : 2022/11/21
//  ------------------------summary--------------------------
//  - �v���C���[
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

    /// �G�l�~�[�������[�h���H�@(EnemeyGenerate)
    bool m_IsGenerateMode = false;

    // why->�G�l�~�[�ɏՓ˂��Ă���,NO_COLL_TIME�b�͓����蔻�薳���ɂ��邽��    
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

