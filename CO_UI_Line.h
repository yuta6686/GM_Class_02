#pragma once
#include "ComponentObject.h"
#include "UserInterfaceComponent.h"
#include "HPComponent.h"
#include "VertexChangeComponent.h"
class CO_UI_Line :
    public ComponentObject
{
public:
    virtual void Init()override
    {
        AddComponent<TransformInit>(COMLAYER_FIRST);

        AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetUnlitShader();

        AddComponent<MatrixComponent>(COMLAYER_MATRIX)->SetIs2D();

        {
            auto* uifc = AddComponent< UserInterfaceComponent>(COMLAYER_DRAW);
            uifc->LoadTexture("asset\\texture\\Line.png");
            uifc->SetDeployIndex(DEPLOY_LEFT_MOVE_RIGHT);
            uifc->SetWidthHeight({ 0.0f,5.0f ,0.0f });
            uifc->SetLeftXPosition(HPComponent::GetLEFTPOSITION());
            uifc->SetRightXPosition(HPComponent::GetRIGHTPOSITION());

        }


        AddComponent<VertexChangeComponent>(COMLAYER_CHANGEVERTEX);

        ComponentObject::Init();
    }
};
