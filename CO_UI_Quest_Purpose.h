#pragma once
#include "ComponentObject.h"
#include "UserInterfaceComponent.h"
#include "VertexChangeComponent.h"

class CO_UI_Quest_Purpose :
    public ComponentObject
{
private:
    float m_Divider = 10.0f;
    D3DXVECTOR3 m_WidthHeight = { 1920.0f,1080,0.0f };
    UserInterfaceComponent* m_UIComponent;
    CountComponent* m_Count;
public:
    virtual void Init()override {
        m_TypeName = "CO_UI_test";

        TransformInit* ti = AddComponent<TransformInit>(COMLAYER_FIRST);
            ti->SetInitPosition({ 1600.0f,750.0f,0.0f });
            ti->SetInitRotation({ 0.0f,0.0f,MyMath::GetRadian(-5.0f )});

        AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetUnlitShader();

        AddComponent<MatrixComponent>(COMLAYER_MATRIX)->SetIs2D();

        m_UIComponent = AddComponent< UserInterfaceComponent>(COMLAYER_DRAW);
        m_UIComponent->LoadTexture("asset\\texture\\purpose.png");
        //  uifc->SetDeployIndex(DEPLOY_LEFTUP);
        D3DXVECTOR3 widthheight = { 1920.0f,1080.0f ,0.0f };
        m_UIComponent->SetWidthHeight(widthheight / m_Divider);
        m_UIComponent->SetIsChangeVertex();

        AddComponent<ImGuiComponent>(COMLAYER_SECOND)->SetIs2D();

        AddComponent<VertexChangeComponent>(COMLAYER_CHANGEVERTEX);

        /* AddComponent<AlphaBlink2DComponent>(COMLAYER_SECOND)
             ->SetParameter(0.01f, 0.5f, 1.0f);*/

        m_Count = AddComponent<CountComponent>(COMLAYER_SECOND);
        m_Count->Start(false, 150, 60);

        ComponentObject::Init();
    }

    virtual void Update()override
    {
        ComponentObject::Update();

        if (m_Count == nullptr)return;
        if (m_Count->GetFinish())
        {
            m_Count->Start(true, 60, 300);
        }

        m_UIComponent->SetAlpha(m_Count->Get0to1Count());
    }

    virtual void DrawImgui()override
    {
        ComponentObject::DrawImgui();

        ImGui::SliderFloat("Divider", &m_Divider, 1.0f, 10.0f, "%.2f");
        m_UIComponent->SetWidthHeight(m_WidthHeight / m_Divider);

        ImGui::Text("count:%d", m_Count->GetCount());
    }
};

