#pragma once
#include "Component.h"
#include "UserInterfaceComponent.h"
#include "manager.h"

class ConfirmationComponent :
    public Component
{
private:    
    UserInterfaceComponent* m_UIComponent;

    const std::string m_MessageBox =
        "asset\\texture\\message_box.png";

    const std::string m_MessageBox_Yes = 
        "asset\\texture\\message_box_Yes.png";

    const std::string m_MessageBox_No =
        "asset\\texture\\message_box_No.png";

    bool m_IsYes = false;
    
public:   
    virtual void Init() override
    {
        m_UIComponent = m_Parent->GetComponent<UserInterfaceComponent>();
        //UserInterfaceComponent* uic = m_Parent->AddComponent<UserInterfaceComponent>(COMLAYER_DRAW);
        //uic->LoadTexture(m_MessageBox_Yes);
        //D3DXVECTOR3 widthheight = { 960.0f,540.0f ,0.0f };
        //uic->SetWidthHeight(widthheight / 3.0f);
        
        m_UIComponent->LoadTexture(m_MessageBox_No);

        m_IsYes = false;
    }

    virtual void Uninit() override
    {
    }

    virtual void Update() override
    {
        if (GetKeyboardTrigger(DIK_LEFT) ||
            GetKeyboardTrigger(DIK_A) &&
            m_IsYes == false)
        {
            m_IsYes = true;
            m_UIComponent->LoadTexture(m_MessageBox_Yes);
        }

        if (GetKeyboardTrigger(DIK_RIGHT) ||
            GetKeyboardTrigger(DIK_D) &&
            m_IsYes == true) {
            m_IsYes = false;
            m_UIComponent->LoadTexture(m_MessageBox_No);
        }
    }

    virtual void Draw() override
    {
    }

    virtual void DrawImgui() override
    {
    }

    bool GetIsYes()const { return m_IsYes; }
    void SetIsYes(const bool& flag) { m_IsYes = flag; }

};

