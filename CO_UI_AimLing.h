#pragma once
#include "ComponentObject.h"
#include "UserInterfaceComponent.h"
#include "VertexChangeComponent.h"
#include "BlinkComponentAlpha2D.h"
#include "BlinkComponent_Scale.h"
#include "Rotate2D.h"
class CO_UI_AimLing :
    public ComponentObject
{
public:
    virtual void Init()override {
        m_TypeName = "CO_UI_test";

        AddComponent<TransformInit>(COMLAYER_FIRST)->
            SetInitPosition({ SCREEN_WIDTH / 2.0f,SCREEN_HEIGHT / 2.0f,0.0f });

        AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetUnlitShader();

        AddComponent<MatrixComponent>(COMLAYER_MATRIX)->SetIs2D();

        auto* uifc = AddComponent< UserInterfaceComponent>(COMLAYER_DRAW);
        uifc->LoadTexture("asset\\texture\\UI_Ling.png");
        //  uifc->SetDeployIndex(DEPLOY_LEFTUP);
        uifc->SetWidthHeight({ 50.0f,50.0f ,0.0f});
        uifc->SetIsChangeVertex();

        AddComponent<ImGuiComponent>(COMLAYER_SECOND)->SetIs2D();

        AddComponent<VertexChangeComponent>(COMLAYER_CHANGEVERTEX);

        AddComponent<AlphaBlink2DComponent>(COMLAYER_SECOND);
        AddComponent< BlinkComponent_Scale>(COMLAYER_SECOND)
            ->SetParameter(AXIS_XYZ,0.1f,1.0f,3.0f);

        AddComponent<Rotate2D>(COMLAYER_SECOND);

        ComponentObject::Init();
    }

};

