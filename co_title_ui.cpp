#include "stdafx.h"
#include "co_title_ui.h"
#include "user_interface_component.h"
#include "blink_scale_component.h"
#include "blink_alpha2d_component.h"
#include "vertex_change_component.h"

void CO_TitleUI::InitInternal()
{
    m_TypeName = "CO_TitleUI";

    AddComponent<TransformInit>(COMLAYER_FIRST)->SetInitPosition({ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 6.0f *5.0f, 0.0f });

    AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetShaderType(SHADER_UNLIT_NO_MATERIAL);

    AddComponent<MatrixComponent>(COMLAYER_MATRIX)->SetIs2D();

    _uiComponent = AddComponent< UserInterfaceComponent>(COMLAYER_DRAW);
    _uiComponent->LoadTexture("asset\\texture\\RightMouseDrag.png");
    D3DXVECTOR3 widthheight = { 960.0f,540.0f ,0.0f };
    _uiComponent->SetWidthHeight(widthheight / 4.0f);
    _uiComponent->SetIsChangeVertex(true);

    BlinkParameter param;
    param._axis = AXIS_XY;
    param._max = 1.0f;
    param._min = 0.8f;
    param._speed = 0.03f;    

    AddComponent<BlinkComponent_Scale>(COMLAYER_SECOND)->SetBlinkParameter(param);
    
    param._min = 0.4f;
    param._max = 1.2f;
    AddComponent<AlphaBlink2DComponent>(COMLAYER_SECOND)->SetBlinkParameter(param);

    AddComponent<VertexChangeComponent>(COMLAYER_CHANGEVERTEX);

    AddComponent<ImGuiComponent>(COMLAYER_SECOND)->SetIsUse(true);
    AddComponent<TitleUI_StateMachine>(COMLAYER_SECOND);
    
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

// https://yuta6686.atlassian.net/browse/AS-52
void TitleUI_StateMachine::InitInternal()
{
    _context->TransitionTo(new TitleUIState_RightMouseDrag());
}

void TitleUIState_RightMouseDrag::Init()
{
    // LoadTexture
    auto uic = _context->m_Parent->GetComponent<UserInterfaceComponent>();
    uic->LoadTexture(TEXTURE);
    D3DXVECTOR3 widthheight = { 960.0f,540.0f ,0.0f };
    uic->SetWidthHeight(widthheight / 4.0f);
}

void TitleUIState_RightMouseDrag::Update()
{
    if (IsMouseRightTriggered()) 
    {
       
        _context->TransitionTo(new TitleUIState_Idle(30));
    }
}

void TitleUIState_Idle::Init()
{
    _context->m_Parent->GetComponent<UserInterfaceComponent>()->_isValidity = false;
}

void TitleUIState_Idle::Update()
{
    // 今はとりあえず、これで実装
    {
        _idleFrame++;

        if (_idleFrame > _idleMaxFrame)
        {
            _idleFrame = 0;
            _context->TransitionTo(new TitleUIState_Space());
        }
    }
}

void TitleUIState_Space::Init()
{
    auto uic =_context->m_Parent->GetComponent<UserInterfaceComponent>();
    uic->_isValidity = true;
    uic->LoadTexture(TEXTURE);
    D3DXVECTOR3 widthheight = { 774.0f,278.0f ,0.0f };
    uic->SetWidthHeight(widthheight / 5.0f);
}

void TitleUIState_Space::Update()
{
// 操作してなかったら、右マウスドラッグ画像に戻る

    // カメラを動かしていなかったら、リセット
    if (IsMouseRightPressed())
        _noOperationFrame = 0;

    _noOperationFrame++;

    if (_noOperationFrame > NO_OPERATION_FRAME_MAX)
    {
        _noOperationFrame = 0;
        _context->TransitionTo(new TitleUIState_RightMouseDrag());
    }
}
