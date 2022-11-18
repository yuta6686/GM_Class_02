#pragma once
#include "component_object.h"
#include "UserInterfaceComponent.h"
#include "HPComponent.h"
#include "VertexChangeComponent.h"

class CO_UI_dot :
    public ComponentObject
{
public:
    virtual void Init()override
    {
        AddComponent<TransformInit>(COMLAYER_FIRST)->
            SetInitPosRot({ 0.0f,50.0f,0.0f },
                { 0.0f,0.0f,MyMath::GetRadian(0.0f) });

        AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetUnlitShader();

        AddComponent<MatrixComponent>(COMLAYER_MATRIX)->SetIs2D();

        {
            auto* uifc = AddComponent< UserInterfaceComponent>(COMLAYER_DRAW);
            uifc->LoadTexture("asset\\texture\\UI_Points.png");
            uifc->SetDeployIndex(DEPLOY_LEFT_MOVE_RIGHT);
            uifc->SetWidthHeight({0.0f,50.0f ,0.0f });
            uifc->SetLeftXPosition(HPComponent::GetLEFTPOSITION() - 25.0f);
            uifc->SetRightXPosition(HPComponent::GetRIGHTPOSITION() + 25.0f);

        }


        AddComponent<VertexChangeComponent>(COMLAYER_CHANGEVERTEX);

        ComponentObject::Init();
    }

    
};

