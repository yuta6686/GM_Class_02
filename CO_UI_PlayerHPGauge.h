#pragma once
#include "ComponentObject.h"
#include "UserInterfaceComponent.h"
#include "VertexChangeComponent.h"
#include "BlinkComponentAlpha2D.h"
#include "BlinkComponent_Scale.h"
#include "Rotate2D.h"

class CO_UI_PlayerHPGauge :
    public ComponentObject
{
public:
    virtual void Init()override
    {
        
        AddComponent<TransformInit>(COMLAYER_FIRST)->
            SetInitPosRot({ 0.0f,50.0f,0.0f }, 
                {0.0f,0.0f,MyMath::GetRadian(0.0f)});

        AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetUnlitShader();

        AddComponent<MatrixComponent>(COMLAYER_MATRIX)->SetIs2D();

        {
            auto* uifc = AddComponent< UserInterfaceComponent>(COMLAYER_DRAW);
            uifc->LoadTexture("asset\\texture\\Line.png");
            uifc->SetDeployIndex(DEPLOY_LEFT_MOVE_RIGHT);
            uifc->SetWidthHeight({ 0.0f,25.0f ,0.0f });
            uifc->SetIsChangeVertex();
            uifc->SetColor({ 0.0f,0.5f,1.0f,1.0f });
        }

        {
            auto* uifc = AddComponent< UserInterfaceComponent>(COMLAYER_DRAW);
            uifc->LoadTexture("asset\\texture\\Line_EndPoint.png");
            uifc->SetDeployIndex(DEPLOY_LEFT_MOVE_RIGHT);
            uifc->SetWidthHeight({ 0.0f,25.0f ,0.0f });
            uifc->SetLeftXPosition(HPComponent::GetLEFTPOSITION());
            uifc->SetRightXPosition(HPComponent::GetRIGHTPOSITION());
        }


        AddComponent<VertexChangeComponent>(COMLAYER_CHANGEVERTEX);

        ComponentObject::Init();
    }
};

