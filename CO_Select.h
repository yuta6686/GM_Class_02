#pragma once
#include "ComponentObject.h"
#include "CO_UI_Select.h"
enum SELECT_NEXT {
    SELECT_NO=-1,
    SELECT_GIVE_UP,
    SELECT_CONTINUE,
    SELECT_RETURN_TO_TITLE,
    SELECT_MAX
};
class CO_Select :
    public ComponentObject
{
private:
    //  �ʏ탁���o�ϐ�
    std::shared_ptr<Scene> m_Scene;

    std::vector<CO_UI_Select*> m_UISelects;
    std::vector<CO_UI_Select*> m_UISelects_String;
    std::vector<CO_UI_Select*> m_UISelects_Box;

    int m_SelectIndex = 0;
    int m_Select = SELECT_NO;
public:

    virtual void Init()override
    {
        m_Scene = Manager::GetScene();

        m_UISelects = m_Scene->GetGameObjects<CO_UI_Select>();

        //  �{�b�N�XUI �� ����UI �� �킯��
        //  �����������Ⴄ���߁B
        for (auto x : m_UISelects)
        {
            if (x->GetIsString()) {
                m_UISelects_String.push_back(x);
            }
            else {
                m_UISelects_Box.push_back(x);
            }

            //  �ʒu���f�t�H���gfalse�Őݒ�
            x->PositionAdaptation(false);
        }
        

        m_SelectIndex = 0;

        ComponentObject::Init();
    }

    virtual void Update()override
    {        

    //  Select-->True
        //  �{�b�N�XUI
        m_UISelects_Box[m_SelectIndex]->GetComponent<UserInterfaceComponent>()->LoadTexture(CO_UI_Select::GetFileName_SelectTrue());
        m_UISelects_Box[m_SelectIndex]->PositionAdaptation(true);

        //  ����UI
        m_UISelects_String[m_SelectIndex]->GetComponent<UserInterfaceComponent>()->SetColor({ 1.0f,0.0f,0.0f,1.0f });       
        m_UISelects_String[m_SelectIndex]->PositionAdaptation(true);

        if (GetKeyboardTrigger(DIK_W))
        {
        //  Select --> False
            //  �{�b�N�XUI
            m_UISelects[m_SelectIndex]->GetComponent<UserInterfaceComponent>()->LoadTexture(CO_UI_Select::GetFileName_SelectFalse());
            m_UISelects_Box[m_SelectIndex]->PositionAdaptation(false);

            //����UI
            m_UISelects_String[m_SelectIndex]->GetComponent<UserInterfaceComponent>()->SetColor({ 1.0f,1.0f,1.0f,1.0f });
            m_UISelects_String[m_SelectIndex]->PositionAdaptation(false);

            //  �C���f�b�N�X����
            m_SelectIndex--;
            if (m_SelectIndex < 0)
            {
                m_SelectIndex = (int)(min(m_UISelects_Box.size(), m_UISelects_Box.size())) - 1;
            }
        }

        if (GetKeyboardTrigger(DIK_S))
        {
        //  Select --> False
            //  �{�b�N�XUI
            m_UISelects[m_SelectIndex]->GetComponent<UserInterfaceComponent>()->LoadTexture(CO_UI_Select::GetFileName_SelectFalse());
            m_UISelects_String[m_SelectIndex]->GetComponent<UserInterfaceComponent>()->SetColor({ 1.0f,1.0f,1.0f,1.0f });

            //����UI
            m_UISelects_Box[m_SelectIndex]->PositionAdaptation(false);
            m_UISelects_String[m_SelectIndex]->PositionAdaptation(false);

            //  �C���f�b�N�X����
            m_SelectIndex++;
            m_SelectIndex %= (int)(min(m_UISelects_Box.size(), m_UISelects_Box.size()));
        }

        //  ���茋�ʂ�ݒ�@�ʒm�͈�x�����B
        if (GetKeyboardTrigger(DIK_SPACE)) {
            m_Select = m_SelectIndex;
        }
        else
        {
            m_Select = SELECT_NO;
        }

        ComponentObject::Update();
    }

    int GetSelect()const { return m_Select; }
};

