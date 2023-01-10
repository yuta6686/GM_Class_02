//  ---------------------------------------------------------
//  JumpComponent [jump_component.cpp]
//                                  Author: ���V�D��
//                                  Date  : 2022/11/21
//  ------------------------summary--------------------------
//  �W�����v
//  
//  �X�y�[�X�������Ƃ��ɁA�x���V�e�B��JUMP�ɂ���
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
    //	�W�����v
    if (GetKeyboardTrigger(DIK_SPACE)) {
        m_VelocityCom->m_Velocity.y = JUMP;
    }
}