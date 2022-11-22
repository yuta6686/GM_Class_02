#include "confirmation_component.h"
#include "audio.h"
#include "user_interface_component.h"

void ConfirmationComponent::Init()
{
    m_UIComponent = m_Parent->GetComponent<UserInterfaceComponent>();
    //UserInterfaceComponent* uic = m_Parent->AddComponent<UserInterfaceComponent>(COMLAYER_DRAW);
    //uic->LoadTexture(m_MessageBox_Yes);
    //D3DXVECTOR3 widthheight = { 960.0f,540.0f ,0.0f };
    //uic->SetWidthHeight(widthheight / 3.0f);

    m_UIComponent->LoadTexture(m_MessageBox_No);

    m_SE = Manager::GetScene()->AddGameObject<Audio>(LAYER_AUDIO);
    m_SE->Load("asset\\audio\\SE_Kettei4.wav");

    m_IsYes = false;
}

void ConfirmationComponent::Uninit()
{
}

void ConfirmationComponent::Update()
{
    if (GetKeyboardTrigger(DIK_LEFT) ||
        GetKeyboardTrigger(DIK_A) &&
        m_IsYes == false)
    {
        m_IsYes = true;
        m_SE->Play(false);
        m_UIComponent->LoadTexture(m_MessageBox_Yes);
    }

    if (GetKeyboardTrigger(DIK_RIGHT) ||
        GetKeyboardTrigger(DIK_D) &&
        m_IsYes == true) {
        m_IsYes = false;
        m_SE->Play(false);
        m_UIComponent->LoadTexture(m_MessageBox_No);
    }
}

void ConfirmationComponent::Draw()
{
}

void ConfirmationComponent::DrawImgui()
{
}