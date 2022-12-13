#include "CO_UI_Quest.h"
#include "user_interface_component.h"
#include "vertex_change_component.h"
#include "blink_alpha2d_component.h"

CO_UI_Quest::CO_UI_Quest()
    :m_Divider(5.0f),
    m_WidthHeight({ SCREEN_WIDTH,SCREEN_HEIGHT,0.0f }),
    _uiComponent(nullptr),
    m_Count(nullptr)
{
}

void CO_UI_Quest::Start()
{
    m_Count->Start(false, 150, 60, 0);
}

void CO_UI_Quest::Init()
{
    m_TypeName = "CO_UI_test";

    AddComponent<TransformInit>(COMLAYER_FIRST)
        ->SetInitPosition({ 1600.0f,700.0f,0.0f }

    );

    AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetShaderType(SHADER_UNLIT);

    AddComponent<MatrixComponent>(COMLAYER_MATRIX)->SetIs2D();

    _uiComponent = AddComponent< UserInterfaceComponent>(COMLAYER_DRAW);
    _uiComponent->LoadTexture("asset\\texture\\UI_black_belt.png");
    //  uifc->SetDeployIndex(DEPLOY_LEFTUP);
    D3DXVECTOR3 widthheight = { 1920.0f,1080.0f ,0.0f };
    _uiComponent->SetWidthHeight(widthheight / 5.0f);
    _uiComponent->SetIsChangeVertex();

    AddComponent<ImGuiComponent>(COMLAYER_SECOND)->SetIs2D();

    AddComponent<VertexChangeComponent>(COMLAYER_CHANGEVERTEX);

    /* AddComponent<AlphaBlink2DComponent>(COMLAYER_SECOND)
         ->SetParameter(0.01f, 0.5f, 1.0f);*/

    m_Count = AddComponent<CountComponent>(COMLAYER_SECOND);
    m_Count->Start(false, 150, 60, 0);

    ComponentObject::Init();
}
void CO_UI_Quest::Update()
{
    ComponentObject::Update();

    if (m_Count == nullptr)return;
    if (m_Count->GetFinish())
    {
        m_Count->Start(true, 60, 120);
    }

    _uiComponent->SetAlpha(m_Count->Get0to1Count());
}

void CO_UI_Quest::DrawImgui()
{
    ComponentObject::DrawImgui();

    ImGui::SliderFloat("Divider", &m_Divider, 1.0f, 10.0f, "%.2f");
    _uiComponent->SetWidthHeight(m_WidthHeight / m_Divider);

    ImGui::Text("count:%d", m_Count->GetCount());
}