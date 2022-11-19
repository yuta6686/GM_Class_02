#pragma once
#include "component_object.h"
#include "user_interface_component.h"
#include "vertex_change_component.h"
#include "blink_alpha2d_component.h"
class CO_UI_Quest_Belt :
    public ComponentObject
{
private:
    float m_Divider = 1.5f;
    D3DXVECTOR3 m_WidthHeight = { 1920.0f,1080.0f,0.0f };
    UserInterfaceComponent* m_UIComponent;
    CountComponent* m_Count;    

    D3DXVECTOR3 m_Departure;
    D3DXVECTOR3 m_Destination;
    bool m_IsReverse = false;
public:
    virtual void Init()override {
        m_TypeName = "CO_UI_test";

        AddComponent<TransformInit>(COMLAYER_FIRST)
            ->SetInitPosition({ SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f,0.0f });

        AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetShaderType(SHADER_UNLIT);

        AddComponent<MatrixComponent>(COMLAYER_MATRIX)->SetIs2D();

        m_UIComponent = AddComponent< UserInterfaceComponent>(COMLAYER_DRAW);
        m_UIComponent->LoadTexture("asset\\texture\\UI_blue_belt.png");
        //  uifc->SetDeployIndex(DEPLOY_LEFTUP);
        D3DXVECTOR3 widthheight = { 1920.0f,1080.0f ,0.0f };
        widthheight /= m_Divider;
        m_UIComponent->SetWidthHeight(widthheight);
        m_UIComponent->SetIsChangeVertex();        

        

        m_Destination = { SCREEN_WIDTH,SCREEN_HEIGHT,0.0f};

        AddComponent<ImGuiComponent>(COMLAYER_SECOND)->SetIs2D();

        AddComponent<VertexChangeComponent>(COMLAYER_CHANGEVERTEX);

        /* AddComponent<AlphaBlink2DComponent>(COMLAYER_SECOND)
             ->SetParameter(0.01f, 0.5f, 1.0f);*/

       m_Count = AddComponent<CountComponent>(COMLAYER_SECOND);
        //m_Count->Start(false, 120, 60);

        ComponentObject::Init();
    }

    void Start(const bool& in, const int& max, const int& delay, bool reverse = false)
    {
        m_IsReverse = reverse;
        if (m_Count == nullptr)return;
        m_Count->Start(in, max, delay);
    }
    void SetDestination(const D3DXVECTOR3& dest) {
        m_Destination = dest;
    }
    void SetDeparture(const D3DXVECTOR3& dep) {
        m_Departure = dep;
    }
    virtual void Update()override
    {
        ComponentObject::Update();

        m_UIComponent->SetAlpha(1.0f);

        if (m_Count == nullptr)return;
        if (m_Count->GetFinish() && m_IsReverse)
        {
            m_Count->Start(true,60,60);
        } 

        D3DXVec3Lerp(&m_Position, &m_Departure, &m_Destination, powf(m_Count->Get0to1Count(),4.0f));
    }

    virtual void DrawImgui()override
    {
        ComponentObject::DrawImgui();

        ImGui::SliderFloat("Divider", &m_Divider, 1.0f, 10.0f, "%.2f");
        m_UIComponent->SetWidthHeight(m_WidthHeight / m_Divider);

        if (m_Count == nullptr)return;

        ImGui::Text("count:%d", m_Count->GetCount());

        if(ImGui::Button("CountStart")) {
            m_Count->Start(false, 60, 0);
        }
    }
};

