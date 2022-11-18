#pragma once
#include "component.h"
#include "gameObject.h"
#include "CountComponent.h"
class VelocityComponent :
    public Component
{
private:
    CountComponent* m_Counter;
    float m_Liner = 1.0f;
    D3DXVECTOR3 m_PreviousVelocity = { 0.0f,0.0f,0.0f };
    const float m_Fast = 1.0f;
    const float m_Late = 0.1f;
    bool m_IsSlow = false;
    bool m_IsBack = false;
    bool m_HasVelocityChanged = false;
    bool m_HasVelocityChanged_Y = false;
    bool m_NoLinerEffect = false;
    bool m_NoAdd = false;

    D3DXVECTOR3 m_OldPos;
public:
    D3DXVECTOR3 m_Velocity = { 0.0f,0.0f,0.0f };
    

    void SetIsSlow(bool flag = true) { m_IsSlow = flag; }
    void SetIsBack(bool flag = true) { m_IsBack = flag; }

    void SetStart(bool in,int max, int delay,int offset) { m_Counter->Start(in, max, delay,offset); }
    
    void SetNoAdd(bool flag = true) { m_NoAdd = flag; }
    void SetOldPos(char xyz) { 
        D3DXVECTOR3 pos = m_Parent->GetPosition();
        switch (xyz)
        {               
        case 'x':
        case 'X':
            pos.x = m_OldPos.x;
            break;
        case 'y':
        case 'Y':
            pos.y = m_OldPos.y;
            break;
        case 'z':
        case 'Z':
            pos.z = m_OldPos.z;
            break;
        default:
            m_Parent->SetPosition(m_OldPos);
            break;
        }        
        m_Parent->SetPosition(pos);
    }

    void SetOldPos(char xyz,float ypos) {
        D3DXVECTOR3 pos = m_Parent->GetPosition();
        switch (xyz)
        {
        case 'x':
        case 'X':
            pos.x = m_OldPos.x;
            break;
        case 'y':
        case 'Y':
            pos.y = ypos;
            break;
        case 'z':
        case 'Z':
            pos.z = m_OldPos.z;
            break;
        default:
            m_Parent->SetPosition(m_OldPos);
            break;
        }
        m_Parent->SetPosition(pos);
    }

    // Component ‚ð‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
    virtual void Init() override
    {
        m_Counter = m_Parent->AddComponent<CountComponent>(COMLAYER_SECOND);

        m_Counter->Start(true, 60, 0,0);

        m_Liner = 1.0f;
    }
    virtual void Uninit() override
    {
    }
    virtual void Update() override
    {
        //  ‘O‚ÌƒtƒŒ[ƒ€‚Ì’l‚ð•Û‘¶
        m_PreviousVelocity = m_Velocity;

        m_OldPos = m_Parent->GetPosition();

        //  •âŠÔˆ—
        if (GetKeyboardTrigger(DIK_G))
        {
            m_IsSlow = true;
        }

        if (GetKeyboardTrigger(DIK_H)) {
            m_IsBack = true;
        }

        if (m_IsSlow ) 
        {
            m_Counter->Start(false, 30, 0,0);
            m_IsSlow = false;
        }

        if (m_IsBack && m_Counter->GetFinish()) {
            m_Counter->Start(true, 30, 60,m_Counter->GetCount());
            m_IsBack = false;
        }
                
                
        MyMath::FloatLerp(&m_Liner, &m_Fast, &m_Late, m_Counter->Get0to1Count());

        // Velocity‚É•Ï‰»‚ª‚È‚¢    “®‚¢‚Ä‚¢‚È‚¢
        if (m_Velocity != m_PreviousVelocity)
            m_HasVelocityChanged = true;        
        else 
            m_HasVelocityChanged = false;
        
        if (m_Velocity.y != m_PreviousVelocity.y) 
            m_HasVelocityChanged_Y = true;        
        else
            m_HasVelocityChanged_Y = false;
        



        //  ¸ŽZ
        if (m_NoAdd)return;

        if (m_NoLinerEffect) 
            m_Parent->AddPosition(m_Velocity);
        else
            m_Parent->AddPosition(m_Velocity * m_Liner);
    }
    virtual void Draw() override
    {
    }
    virtual void DrawImgui() override
    {
        ImGui::Text("aaaaa %.2f", m_Liner);
        ImGui::Text("Get0to1Count %.2f", m_Counter->Get0to1Count());        
    }

    bool GetHasVelocityChanged()const { return m_HasVelocityChanged; }
    bool GetHasVelocityChanged_Y()const { return m_HasVelocityChanged_Y; }

    void SetNoLinerEffect(bool flag = true) { m_NoLinerEffect = flag; }
};

