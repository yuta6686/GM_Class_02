#pragma once
#include "ComponentObject.h"
#include "CO_UI_Select.h"
#include "audio.h"
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
    //  通常メンバ変数
    std::shared_ptr<Scene> m_Scene;

    std::vector<CO_UI_Select*> m_UISelects;
    std::vector<CO_UI_Select*> m_UISelects_String;
    std::vector<CO_UI_Select*> m_UISelects_Box;

    int m_SelectIndex = 0;
    int m_Select = SELECT_NO;

    bool m_IsBlue = false;
    D3DXVECTOR4 m_TrueColor = { 1.0f,0.0f,0.0f,1.0f };

    std::string m_NowFileName_true;
    std::string m_NowFileName_false;

    class Audio* m_SESelect;
    class Audio* m_SEKettei;
public:

    virtual void Init()override
    {
        m_Scene = Manager::GetScene();

        m_UISelects = m_Scene->GetGameObjects<CO_UI_Select>();

        //  ボックスUI と 文字UI に わける
        //  挙動が少し違うため。
        for (auto x : m_UISelects)
        {
            if (x->GetIsString()) {
                m_UISelects_String.push_back(x);
            }
            else {
                m_UISelects_Box.push_back(x);
            }

            //  位置をデフォルトfalseで設定
            x->PositionAdaptation(false);
        }
        

        m_SelectIndex = 0;

        m_NowFileName_true = CO_UI_Select::GetFileName_SelectTrue();
        m_NowFileName_false = CO_UI_Select::GetFileName_SelectFalse();

        m_SESelect = m_Scene->AddGameObject<Audio>(LAYER_AUDIO);
        m_SESelect->Load("asset\\audio\\SE_Scroll.wav");

        m_SEKettei = m_Scene->AddGameObject<Audio>(LAYER_AUDIO);
        m_SEKettei->Load("asset\\audio\\SE_Kettei2.wav");

        ComponentObject::Init();
    }

    virtual void Update()override
    {        

    //  Select-->True
        //  ボックスUI
        m_UISelects_Box[m_SelectIndex]->GetComponent<UserInterfaceComponent>()->LoadTexture(m_NowFileName_true);
        m_UISelects_Box[m_SelectIndex]->PositionAdaptation(true);

        //  文字UI
        m_UISelects_String[m_SelectIndex]->GetComponent<UserInterfaceComponent>()->SetColor(m_TrueColor);
        m_UISelects_String[m_SelectIndex]->PositionAdaptation(true);

        if (GetKeyboardTrigger(DIK_W) || 
            GetKeyboardTrigger(DIK_UP))
        {
        //  Select --> False
            //  ボックスUI
            m_UISelects[m_SelectIndex]->GetComponent<UserInterfaceComponent>()->LoadTexture(m_NowFileName_false);
            m_UISelects_Box[m_SelectIndex]->PositionAdaptation(false);
            m_UISelects_Box[m_SelectIndex]->GetComponent<BlinkComponent_Scale>()
                ->SetParameter(AXIS_XY, 0.0f, 1.0f, 1.0f);

            //文字UI
            m_UISelects_String[m_SelectIndex]->GetComponent<UserInterfaceComponent>()->SetColor({ 1.0f,1.0f,1.0f,1.0f });
            m_UISelects_String[m_SelectIndex]->PositionAdaptation(false);

            //  インデックス処理
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
            //  ボックスUI
            m_UISelects[m_SelectIndex]->GetComponent<UserInterfaceComponent>()->LoadTexture(m_NowFileName_false);
            m_UISelects_String[m_SelectIndex]->GetComponent<UserInterfaceComponent>()->SetColor({ 1.0f,1.0f,1.0f,1.0f });
            m_UISelects_Box[m_SelectIndex]->GetComponent<BlinkComponent_Scale>()
                ->SetParameter(AXIS_XY, 0.0f, 1.0f, 1.0f);

            //文字UI
            m_UISelects_Box[m_SelectIndex]->PositionAdaptation(false);
            m_UISelects_String[m_SelectIndex]->PositionAdaptation(false);

            //  インデックス処理
            m_SelectIndex++;
            m_SelectIndex %= (int)(min(m_UISelects_Box.size(), m_UISelects_Box.size()));


            m_UISelects_Box[m_SelectIndex]->GetComponent<BlinkComponent_Scale>()
                ->SetParameter(AXIS_XY, 0.05f, 1.0f, 1.1f);

            m_SESelect->Play(false);
        }

        //  決定結果を設定　通知は一度だけ。
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

    int GetSelect()const { return m_Select; }
    void SetBlue(bool flag = true) { 
        m_IsBlue = flag; 
        m_TrueColor = { 0.0f,0.25f,0.65f,1.0f };

        m_NowFileName_true = CO_UI_Select::GetFileName_SelectTrue_Blue();
        m_NowFileName_false = CO_UI_Select::GetFileName_SelectFalse_Blue();

        for (auto x : m_UISelects_Box)
        {
            x->GetComponent<UserInterfaceComponent>()->LoadTexture(m_NowFileName_false);
        }
    }
    void SetColor(const D3DXVECTOR4& col) {
        m_TrueColor = col;
    }
};

