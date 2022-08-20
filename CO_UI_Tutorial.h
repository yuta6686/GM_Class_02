#pragma once
#include "ComponentObject.h"
#include "UserInterfaceComponent.h"
#include "VertexChangeComponent.h"
class CO_UI_Tutorial :
    public ComponentObject
{
    UserInterfaceComponent* m_UIComponent;
    CountComponent* m_Count;

    UI_Information m_UIinfo;
    
public:    
    std::string m_Name = "Tutorial";
    void SetColor(const D3DXVECTOR4& col) { m_UIComponent->SetColor(col); }
    void SetTexture(const std::string& tex) { m_UIComponent->LoadTexture(tex); }
    void SetUIComponentInfo(const UI_Information& uii) { 
        m_UIinfo = uii;
        m_UIComponent->SetUIInfo(uii); 
    }
    void CountStart(bool in,
        const int& max,
        const int& delay)
    {
        m_Count->Start(in, max, delay);
    }
    virtual void Init()override {
        m_TypeName = "CO_UI_test";

        AddComponent<TransformInit>(COMLAYER_FIRST)
            ->SetInitPosition({ 300.0f,800.0f,0.0f });

        AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetUnlitShader();

        AddComponent<MatrixComponent>(COMLAYER_MATRIX)->SetIs2D();

        
        

        UI_Information uiinf;
        uiinf._deploy_index = DEPLOY_SEPALATE_UP_DOWN;
        uiinf._texture = "asset\\texture\\gameover_bg.png";

        D3DXVECTOR3 widthheight = { 1500.0f,1080.0f ,0.0f };
        uiinf._main_pos = widthheight / 6.0f;

        uiinf._is_change_vertex = true;
        uiinf._up_pos = -10.0f;
        uiinf._down_pos = 10.0f;

        uiinf._color = { 1.0f,1.0f,1.0f,0.5f };

        m_UIComponent = AddComponent< UserInterfaceComponent>(COMLAYER_DRAW);
        m_UIComponent->SetUIInfo(uiinf);
        
        

        AddComponent<ImGuiComponent>(COMLAYER_SECOND)->SetIs2D();

        AddComponent<VertexChangeComponent>(COMLAYER_CHANGEVERTEX);

        /* AddComponent<AlphaBlink2DComponent>(COMLAYER_SECOND)
             ->SetParameter(0.01f, 0.5f, 1.0f);*/

        

        ComponentObject::Init();
    }

   /* virtual void Update()override
    {
        ComponentObject::Update();

        if (m_Count == nullptr)return;
        if (m_Count->GetFinish())
        {
            m_Count->Start(true, 60, 1 * 60 * 60);
        }

        m_UIComponent->SetAlpha(m_Count->Get0to1Count() * 0.8f);
    }*/

    virtual void DrawImgui()override
    {
        ComponentObject::DrawImgui();

        ImGui::SliderFloat("alpha", &m_UIinfo._color.w, 0.0f, 1.0f, "%.2f");

        ImGui::SliderFloat("width", &m_UIinfo._main_pos.x,0.0f,1000.0f,"%.2f");
        ImGui::SliderFloat("height", &m_UIinfo._main_pos.y, 0.0f, 1000.0f, "%.2f");

        ImGui::SliderFloat("Down Pos", &m_UIinfo._down_pos, 0.0f, 200.0f, "%.2f");
        ImGui::SliderFloat("Up Pos", &m_UIinfo._down_pos, 0.0f, 200.0f, "%.2f");

        SetUIComponentInfo(m_UIinfo);


    }
};

