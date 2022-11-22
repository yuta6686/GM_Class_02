#pragma once
#include "component_object.h"
#include "co_ui_select.h"
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

    virtual void Update()override;

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

