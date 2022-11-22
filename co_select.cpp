#include "co_select.h"

 void CO_Select::Update()
{

    //  Select-->True
        //  �{�b�N�XUI
    m_UISelects_Box[m_SelectIndex]->GetComponent<UserInterfaceComponent>()->LoadTexture(m_NowFileName_true);
    m_UISelects_Box[m_SelectIndex]->PositionAdaptation(true);

    //  ����UI
    m_UISelects_String[m_SelectIndex]->GetComponent<UserInterfaceComponent>()->SetColor(m_TrueColor);
    m_UISelects_String[m_SelectIndex]->PositionAdaptation(true);

    if (GetKeyboardTrigger(DIK_W) ||
        GetKeyboardTrigger(DIK_UP))
    {
        //  Select --> False
            //  �{�b�N�XUI
        m_UISelects[m_SelectIndex]->GetComponent<UserInterfaceComponent>()->LoadTexture(m_NowFileName_false);
        m_UISelects_Box[m_SelectIndex]->PositionAdaptation(false);
        m_UISelects_Box[m_SelectIndex]->GetComponent<BlinkComponent_Scale>()
            ->SetParameter(AXIS_XY, 0.0f, 1.0f, 1.0f);

        //����UI
        m_UISelects_String[m_SelectIndex]->GetComponent<UserInterfaceComponent>()->SetColor({ 1.0f,1.0f,1.0f,1.0f });
        m_UISelects_String[m_SelectIndex]->PositionAdaptation(false);

        //  �C���f�b�N�X����
        m_SelectIndex--;
        if (m_SelectIndex < 0)
        {
            m_SelectIndex = (int)(min(m_UISelects_Box.size(), m_UISelects_Box.size())) - 1;
        }

        m_UISelects_Box[m_SelectIndex]->GetComponent<BlinkComponent_Scale>()
            ->SetParameter(AXIS_XY, 0.05f, 1.0f, 1.1f);

        m_SESelect->Play(false);
    }

    if (GetKeyboardTrigger(DIK_S) ||
        GetKeyboardTrigger(DIK_DOWN))
    {
        //  Select --> False
            //  �{�b�N�XUI
        m_UISelects[m_SelectIndex]->GetComponent<UserInterfaceComponent>()->LoadTexture(m_NowFileName_false);
        m_UISelects_String[m_SelectIndex]->GetComponent<UserInterfaceComponent>()->SetColor({ 1.0f,1.0f,1.0f,1.0f });
        m_UISelects_Box[m_SelectIndex]->GetComponent<BlinkComponent_Scale>()
            ->SetParameter(AXIS_XY, 0.0f, 1.0f, 1.0f);

        //����UI
        m_UISelects_Box[m_SelectIndex]->PositionAdaptation(false);
        m_UISelects_String[m_SelectIndex]->PositionAdaptation(false);

        //  �C���f�b�N�X����
        m_SelectIndex++;
        m_SelectIndex %= (int)(min(m_UISelects_Box.size(), m_UISelects_Box.size()));


        m_UISelects_Box[m_SelectIndex]->GetComponent<BlinkComponent_Scale>()
            ->SetParameter(AXIS_XY, 0.05f, 1.0f, 1.1f);

        m_SESelect->Play(false);
    }

    //  ���茋�ʂ�ݒ�@�ʒm�͈�x�����B
    if (GetKeyboardTrigger(DIK_SPACE)) {
        m_Select = m_SelectIndex;
        m_SEKettei->Play(false);
    }
    else
    {
        m_Select = SELECT_NO;
    }

    ComponentObject::Update();
}