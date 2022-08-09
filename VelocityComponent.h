#pragma once
#include "Component.h"
#include "gameObject.h"
class VelocityComponent :
    public Component
{
private:
    CountComponent* m_Counter;
    D3DXVECTOR3 m_Liner = { 1.0f,1.0f,1.0f };
    const D3DXVECTOR3 m_Fast = { 1.0f,1.0f,1.0f };
    const D3DXVECTOR3 m_Late = { 0.1f,0.1f,0.1f };
    bool m_IsSlow = false;
    bool m_IsBack = false;
public:
    D3DXVECTOR3 m_Velocity = { 0.0f,0.0f,0.0f };

    // Component ‚ð‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
    virtual void Init() override
    {
        m_Counter = m_Parent->AddComponent<CountComponent>(LAYER_3D);

        m_Counter->Start(true, 60, 0);

        m_Liner = { 1.0f,1.0f,1.0f };
    }
    virtual void Uninit() override
    {
    }
    virtual void Update() override
    {
        if (GetKeyboardTrigger(DIK_G))
        {
            m_IsSlow = true;
        }

        if (GetKeyboardTrigger(DIK_H)) {
            m_IsBack = true;
        }

        if (m_IsSlow ) 
        {
            m_Counter->Start(false, 60, 0);
            m_IsSlow = false;
        }

        if (m_IsBack && m_Counter->GetFinish()) {
            m_Counter->Start(true, 60, 0);
            m_IsBack = false;
        }
        
        D3DXVec3Lerp(&m_Liner,&m_Fast,&m_Late,m_Counter->Get0to1Count());
                
        m_Parent->AddPosition(m_Velocity * m_Liner.x);
    }
    virtual void Draw() override
    {
    }
    virtual void DrawImgui() override
    {
        ImGui::Text("aaaaa %.2f", m_Liner.x);
        ImGui::Text("Get0to1Count %.2f", m_Counter->Get0to1Count());        
    }
};

