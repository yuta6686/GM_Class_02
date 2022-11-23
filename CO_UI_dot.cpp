#include "CO_UI_dot.h"
#include "user_interface_component.h"
#include "hp_component.h"
#include "vertex_change_component.h"

void CO_UI_dot::Init()
{
    AddComponent<TransformInit>(COMLAYER_FIRST)->
        SetInitPosRot({ 0.0f,50.0f,0.0f },
            { 0.0f,0.0f,MyMath::GetRadian(0.0f) });

    AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetShaderType(SHADER_UNLIT);

    AddComponent<MatrixComponent>(COMLAYER_MATRIX)->SetIs2D();

    {
        auto* uifc = AddComponent< UserInterfaceComponent>(COMLAYER_DRAW);
        uifc->LoadTexture("asset\\texture\\UI_Points.png");
        uifc->SetDeployIndex(DEPLOY_LEFT_MOVE_RIGHT);
        uifc->SetWidthHeight({ 0.0f,50.0f ,0.0f });
        uifc->SetLeftXPosition(HPComponent::GetLEFTPOSITION() - 25.0f);
        uifc->SetRightXPosition(HPComponent::GetRIGHTPOSITION() + 25.0f);

    }


    AddComponent<VertexChangeComponent>(COMLAYER_CHANGEVERTEX);

    ComponentObject::Init();
}
