#include "stdafx.h"
#include "CO_UI_Tutorial.h"


void CO_UI_Tutorial::Init()
{
    m_TypeName = "CO_UI_test";

    AddComponent<TransformInit>(COMLAYER_FIRST)
        ->SetInitPosition({ 300.0f,800.0f,0.0f });

    AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetShaderType(SHADER_UNLIT);

    AddComponent<MatrixComponent>(COMLAYER_MATRIX)->SetIs2D();




    UI_Information uiinf;
    uiinf._deploy_index = DEPLOY_SEPALATE_UP_DOWN;
    uiinf._texture = "asset\\texture\\gameover_bg.dds";

    D3DXVECTOR3 widthheight = { 1500.0f,1080.0f ,0.0f };
    uiinf._main_pos = widthheight / 6.0f;

    uiinf._is_change_vertex = true;
    uiinf._up_pos = -10.0f;
    uiinf._down_pos = 10.0f;

    uiinf._color = { 1.0f,1.0f,1.0f,0.5f };

    _uiComponent = AddComponent< UserInterfaceComponent>(COMLAYER_DRAW);
    _uiComponent->SetUIInfo(uiinf);



    AddComponent<ImGuiComponent>(COMLAYER_SECOND)->SetIs2D();

    AddComponent<VertexChangeComponent>(COMLAYER_CHANGEVERTEX);

    /* AddComponent<AlphaBlink2DComponent>(COMLAYER_SECOND)
         ->SetParameter(0.01f, 0.5f, 1.0f);*/



    ComponentObject::Init();
}

void CO_UI_Tutorial::DrawImgui()
{
    ComponentObject::DrawImgui();

    ImGui::SliderFloat("alpha", &m_UIinfo._color.w, 0.0f, 1.0f, "%.2f");

    ImGui::SliderFloat("width", &m_UIinfo._main_pos.x, 0.0f, 1000.0f, "%.2f");
    ImGui::SliderFloat("height", &m_UIinfo._main_pos.y, 0.0f, 1000.0f, "%.2f");

    ImGui::SliderFloat("Down Pos", &m_UIinfo._down_pos, 0.0f, 200.0f, "%.2f");
    ImGui::SliderFloat("Up Pos", &m_UIinfo._down_pos, 0.0f, 200.0f, "%.2f");

    SetUIComponentInfo(m_UIinfo);


}
/* virtual void Update()override
 {
     ComponentObject::Update();

     if (m_Count == nullptr)return;
     if (m_Count->GetFinish())
     {
         m_Count->Start(true, 60, 1 * 60 * 60);
     }

     _uiComponent->SetAlpha(m_Count->Get0to1Count() * 0.8f);
 }*/