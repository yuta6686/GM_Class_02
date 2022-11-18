#pragma once
#include "component_object.h"
#include "CO_UI_Tutorial.h"

#include "manager.h"
class CO_UI_Tutorial_Move2 :
    public ComponentObject
{
private:
    std::vector<CO_UI_Tutorial*> m_Tutorial;
    std::shared_ptr<Scene> m_Scene;

    
    
    CountComponent* m_Count;

    bool m_IsCharge = false;
    bool m_IsShoot = false;    

    inline static const D3DXVECTOR4 CLEAR_COLOR = { 0.0f,0.0f,0.0f,0.75f };
    inline static const D3DXVECTOR4 ACTION_COLOR = { 0.0f,0.5f,1.0f,0.75f };
    inline static const D3DXVECTOR4 NO_ACTION_COLOR = { 1.0f,1.0f,1.0f,0.25f };
public:
    virtual void Init()override
    {
        m_Scene = Manager::GetScene();
        

        //  下地 テクスチャ 0
        {
            CO_UI_Tutorial* tut = m_Scene->AddGameObject<CO_UI_Tutorial>(LAYER_2D);

            UI_Information uiinf;
            uiinf._deploy_index = DEPLOY_SEPALATE_UP_DOWN;
            uiinf._texture = "asset\\texture\\gameover_bg.png";

            D3DXVECTOR3 widthheight = { 1500.0f,1080.0f ,0.0f };
            uiinf._main_pos = widthheight / 5.0f;

            uiinf._is_change_vertex = true;
            uiinf._up_pos = -10.0f;
            uiinf._down_pos = 10.0f;

            uiinf._color = { 1.0f,1.0f,1.0f,0.75f };

            tut->SetUIComponentInfo(uiinf);

            tut->SetPosition({ 300.0f,750.0f,0.0f });

            tut->m_Name = "Under Texture";

            m_Tutorial.push_back(tut);
        }

        //  ラベル テクスチャ 1
        {
            CO_UI_Tutorial* tut = m_Scene->AddGameObject<CO_UI_Tutorial>(LAYER_2D);

            UI_Information uiinf;
            uiinf._deploy_index = DEPLOY_SEPALATE_UP_DOWN;
            uiinf._texture = "asset\\texture\\label_white.png";

            D3DXVECTOR3 widthheight = { 250.0f,40.0f ,0.0f };
            uiinf._main_pos = widthheight;

            uiinf._is_change_vertex = true;
            uiinf._up_pos = -5.0f;
            uiinf._down_pos = 5.0f;

            uiinf._color = { 1.0f,1.0f,1.0f,1.0f };

            tut->SetUIComponentInfo(uiinf);

            tut->SetPosition({ 300.0f,630.0f,0.0f });

            tut->m_Name = "Label_001";

            m_Tutorial.push_back(tut);
        }

        //  ラベル テクスチャ 2
        {
            CO_UI_Tutorial* tut = m_Scene->AddGameObject<CO_UI_Tutorial>(LAYER_2D);

            UI_Information uiinf;
            uiinf._deploy_index = DEPLOY_SEPALATE_UP_DOWN;
            uiinf._texture = "asset\\texture\\label_white.png";

            D3DXVECTOR3 widthheight = { 250.0f,40.0f ,0.0f };
            uiinf._main_pos = widthheight;

            uiinf._is_change_vertex = true;
            uiinf._up_pos = -5.0f;
            uiinf._down_pos = 5.0f;

            uiinf._color = { 1.0f,1.0f,1.0f,1.0f };

            tut->SetUIComponentInfo(uiinf);

            tut->SetPosition({ 300.0f,750.0f,0.0f });

            tut->m_Name = "Label_003";

            m_Tutorial.push_back(tut);
        }

        //  charge 4
        {
            CO_UI_Tutorial* tut = m_Scene->AddGameObject<CO_UI_Tutorial>(LAYER_2D);

            UI_Information uiinf;
            uiinf._deploy_index = DEPLOY_SEPALATE_UP_DOWN;
            uiinf._texture = "asset\\texture\\Tutorial_charge.png";

            D3DXVECTOR3 widthheight = { 1500.0f,400.0f ,0.0f };
            uiinf._main_pos = widthheight / 10.0f;

            uiinf._is_change_vertex = true;
            uiinf._up_pos = -5.0f;
            uiinf._down_pos = 5.0f;

            uiinf._color = { 1.0f,1.0f,1.0f,1.0f };

            tut->SetUIComponentInfo(uiinf);

            tut->SetPosition({ 300.0f,750.0f,0.0f });

            tut->m_Name = "Charge";

            m_Tutorial.push_back(tut);
        }
        //  ショット 5
        {
            CO_UI_Tutorial* tut = m_Scene->AddGameObject<CO_UI_Tutorial>(LAYER_2D);

            UI_Information uiinf;
            uiinf._deploy_index = DEPLOY_SEPALATE_UP_DOWN;
            uiinf._texture = "asset\\texture\\Tutorial_shoot.png";

            D3DXVECTOR3 widthheight = { 1500.0f,400.0f ,0.0f };
            uiinf._main_pos = widthheight / 10.0f;

            uiinf._is_change_vertex = true;
            uiinf._up_pos = -5.0f;
            uiinf._down_pos = 5.0f;

            uiinf._color = { 1.0f,1.0f,1.0f,1.0f };

            tut->SetUIComponentInfo(uiinf);

            tut->SetPosition({ 300.0f,630.0f,0.0f });

            tut->m_Name = "Shoot";

            m_Tutorial.push_back(tut);
        }


        
        m_Count = AddComponent<CountComponent>(COMLAYER_SECOND);
        m_Count->Start(false, 60, 60, 0);
        
        

        m_IsCharge = false;
        m_IsShoot = false;
        


        ComponentObject::Init();
    }

    virtual void Update()override
    {
        ComponentObject::Update();



        //  チャージ
        if (IsMouseLeftPressed()) {
            m_IsCharge = true;
            m_Tutorial[2]->SetColor(ACTION_COLOR);
            m_Tutorial[4]->SetColor(NO_ACTION_COLOR);
        }
        else
        {
            if (m_IsCharge) {
                m_Tutorial[2]->SetColor(CLEAR_COLOR);
                m_Tutorial[3]->SetColor(NO_ACTION_COLOR);
            }
            else {
                m_Tutorial[2]->SetColor(NO_ACTION_COLOR);
                m_Tutorial[3]->SetColor(ACTION_COLOR);
            }
        }

        //  ショット 
        if (ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
            m_IsShoot = true;
            m_Tutorial[1]->SetColor(ACTION_COLOR);
            m_Tutorial[4]->SetColor(NO_ACTION_COLOR);            
        }
        else
        {
            if (m_IsShoot) {
                m_Tutorial[1]->SetColor(CLEAR_COLOR);
                m_Tutorial[4]->SetColor(NO_ACTION_COLOR);
            }
            else {
                m_Tutorial[1]->SetColor(NO_ACTION_COLOR);
                m_Tutorial[4]->SetColor(ACTION_COLOR);
            }
        }




        if (m_Count == nullptr)return;
        if (m_Count->GetFinish() && m_IsCharge && m_IsShoot)
        {
            m_Count->Start(true, 60, 60);
        }

        if (m_Count->GetInFinist()) {            
            for (auto tut : m_Tutorial)
            {
                tut->SetDestroy();
            }
            this->SetDestroy();
            return;
        }

        for (auto tuto : m_Tutorial) {
            tuto->GetComponent<UserInterfaceComponent>()->SetAlpha(m_Count->Get0to1Count() * 0.8f);
        }

    }
};

