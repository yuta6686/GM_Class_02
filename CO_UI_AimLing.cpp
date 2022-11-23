#include "CO_UI_AimLing.h"
#include "user_interface_component.h"
#include "vertex_change_component.h"
#include "blink_alpha2d_component.h"
#include "blink_scale_component.h"
#include "rotate2d_component.h"


void CO_UI_AimLing::Init()
{
    m_TypeName = "CO_UI_test";


    AddComponent<TransformInit>(COMLAYER_FIRST)->
        SetInitPosition({ SCREEN_WIDTH / 2.0f,SCREEN_HEIGHT / 2.0f,0.0f });

    AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetShaderType(SHADER_UNLIT);

    AddComponent<MatrixComponent>(COMLAYER_MATRIX)->SetIs2D();

    auto* uifc = AddComponent< UserInterfaceComponent>(COMLAYER_DRAW);
    uifc->LoadTexture("asset\\texture\\UI_Ling.png");
    //  uifc->SetDeployIndex(DEPLOY_LEFTUP);
    uifc->SetWidthHeight({ 50.0f,50.0f ,0.0f });
    uifc->SetIsChangeVertex();

    AddComponent<ImGuiComponent>(COMLAYER_SECOND)->SetIs2D();

    AddComponent<VertexChangeComponent>(COMLAYER_CHANGEVERTEX);

    AddComponent<AlphaBlink2DComponent>(COMLAYER_SECOND);
    AddComponent< BlinkComponent_Scale>(COMLAYER_SECOND)
        ->SetParameter(AXIS_XYZ, 0.1f, 1.0f, 3.0f);

    AddComponent<Rotate2D>(COMLAYER_SECOND);

    ComponentObject::Init();
}
