#pragma once
#include "ComponentObject.h"
#include "CO_UI_Tutorial.h"
#include "manager.h"

class CO_UI_Tutorial_Move :
    public ComponentObject
{
private:
    std::vector<CO_UI_Tutorial*> m_Tutorial;
    std::shared_ptr<Scene> m_Scene;

    CountComponent* m_Count;
public:
    virtual void Init()override
    {
        m_Scene = Manager::GetScene();

        //  下地 テクスチャ 0
        {
            CO_UI_Tutorial* tut = m_Scene->AddGameObject<CO_UI_Tutorial>(LAYER_3D);

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
            CO_UI_Tutorial* tut = m_Scene->AddGameObject<CO_UI_Tutorial>(LAYER_3D);

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
            CO_UI_Tutorial* tut = m_Scene->AddGameObject<CO_UI_Tutorial>(LAYER_3D);

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

        //  ラベル テクスチャ 3
        {
            CO_UI_Tutorial* tut = m_Scene->AddGameObject<CO_UI_Tutorial>(LAYER_3D);

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

            tut->SetPosition({ 300.0f,870,0.0f });

            tut->m_Name = "Label_002";

            m_Tutorial.push_back(tut);
        }

        //  移動 4
        {
            CO_UI_Tutorial* tut = m_Scene->AddGameObject<CO_UI_Tutorial>(LAYER_3D);

            UI_Information uiinf;
            uiinf._deploy_index = DEPLOY_SEPALATE_UP_DOWN;
            uiinf._texture = "asset\\texture\\Tutorial_move.png";

            D3DXVECTOR3 widthheight = { 1500.0f,400.0f ,0.0f };
            uiinf._main_pos = widthheight / 10.0f;

            uiinf._is_change_vertex = true;
            uiinf._up_pos = -5.0f;
            uiinf._down_pos = 5.0f;

            uiinf._color = { 1.0f,1.0f,1.0f,1.0f };

            tut->SetUIComponentInfo(uiinf);

            tut->SetPosition({ 300.0f,750.0f,0.0f });

            tut->m_Name = "Movement";

            m_Tutorial.push_back(tut);
        }
        //  ジャンプ 5
        {
            CO_UI_Tutorial* tut = m_Scene->AddGameObject<CO_UI_Tutorial>(LAYER_3D);

            UI_Information uiinf;
            uiinf._deploy_index = DEPLOY_SEPALATE_UP_DOWN;
            uiinf._texture = "asset\\texture\\Tutorial_jump.png";

            D3DXVECTOR3 widthheight = { 1500.0f,400.0f ,0.0f };
            uiinf._main_pos = widthheight / 10.0f;

            uiinf._is_change_vertex = true;
            uiinf._up_pos = -5.0f;
            uiinf._down_pos = 5.0f;

            uiinf._color = { 1.0f,1.0f,1.0f,1.0f };

            tut->SetUIComponentInfo(uiinf);

            tut->SetPosition({ 300.0f,630.0f,0.0f });

            tut->m_Name = "Jump";

            m_Tutorial.push_back(tut);
        }

        //  視点移動 6
        {
            CO_UI_Tutorial* tut = m_Scene->AddGameObject<CO_UI_Tutorial>(LAYER_3D);

            UI_Information uiinf;
            uiinf._deploy_index = DEPLOY_SEPALATE_UP_DOWN;
            uiinf._texture = "asset\\texture\\Tutorial_ray_move.png";

            D3DXVECTOR3 widthheight = { 1500.0f,400.0f ,0.0f };
            uiinf._main_pos = widthheight / 10.0f;

            uiinf._is_change_vertex = true;
            uiinf._up_pos = -5.0f;
            uiinf._down_pos = 5.0f;

            uiinf._color = { 1.0f,1.0f,1.0f,1.0f };

            tut->SetUIComponentInfo(uiinf);

            tut->SetPosition({ 300.0f,870,0.0f });

            tut->m_Name = "RayMove";

            m_Tutorial.push_back(tut);
        }
        
        m_Count = AddComponent<CountComponent>(COMLAYER_SECOND);
        m_Count->Start(false, 60, 60, 0);

        ComponentObject::Init();
    }

    virtual void Update()override
    {
        ComponentObject::Update();

        if (GetKeyboardPress(DIK_W) ||
            GetKeyboardPress(DIK_S) ||
            GetKeyboardPress(DIK_A) ||
            GetKeyboardPress(DIK_D)) {
            m_Tutorial[2]->SetColor({ 1.0f,1.0f,1.0f,0.75f });
            m_Tutorial[4]->SetColor({ 0.0f,1.0f,1.0f,0.75f });
        }
        else
        {
            m_Tutorial[2]->SetColor({ 0.0f,1.0f,1.0f,0.75f });
            m_Tutorial[4]->SetColor({ 1.0f,1.0f,1.0f,0.75f });
        }
        
        if (GetKeyboardPress(DIK_SPACE)) {
            m_Tutorial[1]->SetColor({ 1.0f,1.0f,1.0f,0.75f });
            m_Tutorial[5]->SetColor({ 0.0f,1.0f,1.0f,0.75f });
        }
        else
        {
            m_Tutorial[1]->SetColor({ 0.0f,1.0f,1.0f,0.75f });
            m_Tutorial[5]->SetColor({ 1.0f,1.0f,1.0f,0.75f });
        }

        if (IsMouseRightPressed()) {

            m_Tutorial[3]->SetColor({ 1.0f,1.0f,1.0f,0.75f });
            m_Tutorial[6]->SetColor({ 0.0f,1.0f,1.0f,0.75f });
        }
        else
        {
            m_Tutorial[3]->SetColor({ 0.0f,1.0f,1.0f,0.75f });
            m_Tutorial[6]->SetColor({ 1.0f,1.0f,1.0f,0.75f });
        }

        

        if (m_Count == nullptr)return;
        if (m_Count->GetFinish())
        {
            m_Count->Start(true, 60, 15 * 60);
        }

        for (auto tuto : m_Tutorial) {
            tuto->GetComponent<UserInterfaceComponent>()->SetAlpha(m_Count->Get0to1Count() * 0.8f);
        }
        
    }
};

