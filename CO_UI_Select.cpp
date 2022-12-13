#include "stdafx.h"
#include "co_ui_select.h"
#include "user_interface_component.h"
#include "hp_component.h"
#include "vertex_change_component.h"
#include "blink_scale_component.h"

void CO_UI_Select::Init()

{
    AddComponent<TransformInit>(COMLAYER_FIRST);

    AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetShaderType(SHADER_UNLIT);

    AddComponent<MatrixComponent>(COMLAYER_MATRIX)->SetIs2D();

    {
        auto* uifc = AddComponent< UserInterfaceComponent>(COMLAYER_DRAW);

        for (auto x : m_FileNameBox) {
            uifc->LoadTexture(x);
        }

        uifc->LoadTexture(m_FileName_Select_True);
        uifc->LoadTexture(m_FileName_Select_False);


        uifc->SetDeployIndex(DEPLOY_CENTER);
        uifc->SetWidthHeight({ 275.0f,30.0f ,0.0f });
        uifc->SetIsChangeVertex();
        //uifc->SetLeftXPosition(HPComponent::GetLEFTPOSITION() - 25.0f);
        //uifc->SetRightXPosition(HPComponent::GetRIGHTPOSITION() + 25.0f);

    }



    AddComponent<VertexChangeComponent>(COMLAYER_CHANGEVERTEX);

    AddComponent<BlinkComponent_Scale>(COMLAYER_SECOND)
        ->SetParameter(AXIS_XY, 0.0f, 1.0f, 1.0f);

    ComponentObject::Init();
}

void CO_UI_Select::SetTrue_False_Position(const D3DXVECTOR3& true_pos, const float& up)
{
    m_TruePosition = true_pos;
    m_FalsePosition = true_pos;
    m_FalsePosition.y -= up;
}

D3DXVECTOR3 CO_UI_Select::GetTrue_False_Position(bool flag)
{
    if (flag)
        return m_TruePosition;

    return m_FalsePosition;
}

void CO_UI_Select::PositionAdaptation(bool flag)
{
    if (flag)
        m_Position = m_TruePosition;
    else
        m_Position = m_FalsePosition;
}