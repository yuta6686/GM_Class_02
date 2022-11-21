//  ---------------------------------------------------------
//  JumpComponent [jump_component.cpp]
//                                  Author: 柳澤優太
//                                  Date  : 2022/11/21
//  ------------------------summary--------------------------
//  ジャンプ
//  
//  スペース押したときに、ベロシティをJUMPにする
//  ---------------------------------------------------------
#include "jump_component.h"
#include "velocity_component.h"

void JumpComponent::Init()
{
    m_VelocityCom = m_Parent->AddComponent<VelocityComponent>(COMLAYER_SECOND);
    m_VelocityCom->SetNoLinerEffect();
    m_VelocityCom->SetNoAdd();

    m_Scene = Manager::GetScene();
}

void JumpComponent::Update()
{
    //	ジャンプ
    if (GetKeyboardTrigger(DIK_SPACE)) {
        m_VelocityCom->m_Velocity.y = JUMP;
    }
}