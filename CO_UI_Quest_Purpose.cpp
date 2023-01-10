#include "CO_UI_Quest_Purpose.h"
#include "user_interface_component.h"
#include "vertex_change_component.h"

CO_UI_Quest_Purpose::CO_UI_Quest_Purpose()
    :m_Divider(10.0f),
    m_WidthHeight({ 1920.0f,1080,0.0f }),
    _uiComponent(nullptr),m_Count(nullptr)
{
}

void CO_UI_Quest_Purpose::Start()
{
    m_Count->Start(false, 150, 60);
}

void CO_UI_Quest_Purpose::SetTexture(std::string file)
{
    _uiComponent->LoadTexture(file.c_str());
}


void CO_UI_Quest_Purpose::Init()
{
    m_TypeName = "CO_UI_test";

    TransformInit* ti = AddComponent<TransformInit>(COMLAYER_FIRST);
    ti->SetInitPosition({ 1600.0f,750.0f,0.0f });
    ti->SetInitRotation({ 0.0f,0.0f,MyMath::GetRadian(-5.0f) });

    AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetShaderType(SHADER_UNLIT);

    AddComponent<MatrixComponent>(COMLAYER_MATRIX)->SetIs2D();

    _uiComponent = AddComponent< UserInterfaceComponent>(COMLAYER_DRAW);
    _uiComponent->LoadTexture("asset\\texture\\purpose.png");
    //  uifc->SetDeployIndex(DEPLOY_LEFTUP);
    D3DXVECTOR3 widthheight = { 1920.0f,1080.0f ,0.0f };
    _uiComponent->SetWidthHeight(widthheight / m_Divider);
    _uiComponent->SetIsChangeVertex();

    AddComponent<ImGuiComponent>(COMLAYER_SECOND)->SetIs2D();

    AddComponent<VertexChangeComponent>(COMLAYER_CHANGEVERTEX);

    /* AddComponent<AlphaBlink2DComponent>(COMLAYER_SECOND)
         ->SetParameter(0.01f, 0.5f, 1.0f);*/

    m_Count = AddComponent<CountComponent>(COMLAYER_SECOND);
    m_Count->Start(false, 150, 60);

    ComponentObject::Init();
}

void CO_UI_Quest_Purpose::Update()
{
    ComponentObject::Update();

    if (m_Count == nullptr)return;
    if (m_Count->GetFinish())
    {
        m_Count->Start(true, 60, 120);
    }

    _uiComponent->SetAlpha(m_Count->Get0to1Count());
}

void CO_UI_Quest_Purpose::DrawImgui()
{
    ComponentObject::DrawImgui();

    ImGui::SliderFloat("Divider", &m_Divider, 1.0f, 10.0f, "%.2f");
    _uiComponent->SetWidthHeight(m_WidthHeight / m_Divider);

    ImGui::Text("count:%d", m_Count->GetCount());
}