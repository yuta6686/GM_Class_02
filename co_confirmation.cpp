#include "co_confirmation.h"
#include "user_interface_component.h"
#include "vertex_change_component.h"
#include "blink_alpha2d_component.h"
#include "blink_scale_component.h"
#include "rotate2d_component.h"
#include "confirmation_component.h"

 void CO_Confirmation::Init()
{
    m_TypeName = "CO_Confirmation";

    AddComponent<TransformInit>(COMLAYER_FIRST)->SetInitPosition({ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f });

    AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetShaderType(SHADER_UNLIT_NO_MATERIAL);

    AddComponent<MatrixComponent>(COMLAYER_MATRIX)->SetIs2D();

    UserInterfaceComponent* uic = AddComponent< UserInterfaceComponent>(COMLAYER_DRAW);
    uic->LoadTexture("asset\\texture\\message_box.png");
    D3DXVECTOR3 widthheight = { 960.0f,540.0f ,0.0f };
    uic->SetWidthHeight(widthheight / 3.0f);

    UserInterfaceComponent* uic_ = AddComponent< UserInterfaceComponent>(COMLAYER_DRAW);
    uic_->LoadTexture("asset\\texture\\message_exit.png");
    uic_->SetWidthHeight(widthheight / 3.0f);

    AddComponent<ImGuiComponent>(COMLAYER_SECOND)->SetIs2D();

    AddComponent< ConfirmationComponent>(COMLAYER_SECOND);

    ComponentObject::Init();
}
