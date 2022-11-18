#pragma once
#include "component.h"
#include "velocity_component.h"
#include "manager.h"
#include "Cylinder.h"

class JumpComponent :
    public Component
{
private:
    inline static const float JUMP = 0.6f;
    inline static const float GRAVITY = 0.01f;
    inline static const D3DXVECTOR3 ATTENUATION = { 0.9f,0.99f,0.9f };        

    std::shared_ptr<Scene> m_Scene;
public:
    VelocityComponent* m_VelocityCom;

    virtual void Init() override
    {
        m_VelocityCom = m_Parent->AddComponent<VelocityComponent>(COMLAYER_SECOND);
        m_VelocityCom->SetNoLinerEffect();
        m_VelocityCom->SetNoAdd();

        m_Scene = Manager::GetScene();
    }
    virtual void Uninit() override
    {
    }
    virtual void Update() override
    {
        //	ƒWƒƒƒ“ƒv
        if (GetKeyboardTrigger(DIK_SPACE)) {
            m_VelocityCom->m_Velocity.y = JUMP;
        }
        

        //m_VelocityCom->m_Velocity.y *= ATTENUATION.y;



    }
    virtual void Draw() override
    {
    }
    virtual void DrawImgui() override
    {
        //if (ImGui::Button("Player->Jump")) {
        //    if (m_Parent->GetPosition().y >= 0.2f) {
        //        m_VelocityCom->m_Velocity.y = JUMP * 1.5f;
        //    }
        //    else {
        //        m_VelocityCom->m_Velocity.y = JUMP;
        //    }
        //}
    }
};

