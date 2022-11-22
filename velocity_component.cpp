#include "velocity_component.h"
#include "count_component.h"

VelocityComponent::VelocityComponent()
    :m_Counter(nullptr),
    m_Liner(1.0f),
    m_PreviousVelocity({ 0.0f,0.0f,0.0f }),
    m_IsSlow(false),
    m_IsBack(false),
    m_HasVelocityChanged(false),
    m_HasVelocityChanged_Y(false),
    m_NoLinerEffect(false),
    m_NoAdd(false),
    m_OldPos({ 0.0f,0.0f,0.0f }),
    m_Velocity({ 0.0f,0.0f,0.0f }) {}


void VelocityComponent::SetOldPos(char xyz)
{
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

void VelocityComponent::SetOldPos(char xyz, float ypos)
{
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

void VelocityComponent::Init()
{
    m_Counter = m_Parent->AddComponent<CountComponent>(COMLAYER_SECOND);

    m_Counter->Start(true, 60, 0, 0);

    m_Liner = 1.0f;
}

void VelocityComponent::Uninit()
{
}

void VelocityComponent::Update()
{    //  前のフレームの値を保存
    m_PreviousVelocity = m_Velocity;

    m_OldPos = m_Parent->GetPosition();

    //  補間処理
    if (GetKeyboardTrigger(DIK_G))
    {
        m_IsSlow = true;
    }

    if (GetKeyboardTrigger(DIK_H)) {
        m_IsBack = true;
    }

    if (m_IsSlow)
    {
        m_Counter->Start(false, 30, 0, 0);
        m_IsSlow = false;
    }

    if (m_IsBack && m_Counter->GetFinish()) {
        m_Counter->Start(true, 30, 60, m_Counter->GetCount());
        m_IsBack = false;
    }


    MyMath::FloatLerp(&m_Liner, &FAST, &LATE, m_Counter->Get0to1Count());

    // Velocityに変化がない  ＝  動いていない
    if (m_Velocity != m_PreviousVelocity)
        m_HasVelocityChanged = true;
    else
        m_HasVelocityChanged = false;

    if (m_Velocity.y != m_PreviousVelocity.y)
        m_HasVelocityChanged_Y = true;
    else
        m_HasVelocityChanged_Y = false;




    //  精算
    if (m_NoAdd)return;

    if (m_NoLinerEffect)
        m_Parent->AddPosition(m_Velocity);
    else
        m_Parent->AddPosition(m_Velocity * m_Liner);
}

void VelocityComponent::Draw()
{
    ImGui::Text("aaaaa %.2f", m_Liner);
    ImGui::Text("Get0to1Count %.2f", m_Counter->Get0to1Count());
}

void VelocityComponent::DrawImgui()
{
}

void VelocityComponent::SetStart(const bool& in,
    const int& max, const int& delay, const int& offset)
{ 
    m_Counter->Start(in, max, delay, offset); 
}
