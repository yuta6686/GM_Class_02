#include "stdafx.h"
#include "co_title_ui.h"
#include "user_interface_component.h"
#include "blink_scale_component.h"
#include "blink_alpha2d_component.h"
#include "vertex_change_component.h"

void CO_TitleUI::InitInternal()
{
    m_TypeName = "CO_TitleUI";

    AddComponent<TransformInit>(COMLAYER_FIRST)->SetInitPosition({ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 5.0f * 4.0f, 0.0f });

    AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetShaderType(SHADER_UNLIT_NO_MATERIAL);

    AddComponent<MatrixComponent>(COMLAYER_MATRIX)->SetIs2D();

    UserInterfaceComponent* _uiComponent = AddComponent< UserInterfaceComponent>(COMLAYER_DRAW);
    _uiComponent->LoadTexture("asset\\texture\\RightMouseDrag.png");
    D3DXVECTOR3 widthheight = { 960.0f,540.0f ,0.0f };
    _uiComponent->SetWidthHeight(widthheight / 4.0f);
    _uiComponent->SetIsChangeVertex(true);

    BlinkParameter param;
    param._axis = AXIS_XY;
    param._max = 1.2f;
    param._min = 0.8f;
    param._speed = 0.07f;    

    AddComponent<BlinkComponent_Scale>(COMLAYER_SECOND)->SetBlinkParameter(param);
    
    param._min = 0.4f;
    param._max = 1.2f;
    AddComponent<AlphaBlink2DComponent>(COMLAYER_SECOND)->SetBlinkParameter(param);

    AddComponent<VertexChangeComponent>(COMLAYER_CHANGEVERTEX);

    AddComponent<ImGuiComponent>(COMLAYER_SECOND)->SetIsUse(true);
    
    
}

void CO_TitleUI::UninitInternal()
{
}

void CO_TitleUI::UpdateInternal()
{
    if (IsMouseRightTriggered())
    {
        
    }
        
}

void CO_TitleUI::DrawInternal()
{
}

void CO_TitleUI::DrawImguiInternal()
{
}
