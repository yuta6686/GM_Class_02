#pragma once
#include "ComponentObject.h"
#include "UserInterfaceComponent.h"
#include "VertexChangeComponent.h"
class CO_UI_AimLing :
    public ComponentObject
{
public:
    virtual void Init()override {
        m_TypeName = "CO_UI_test";

        AddComponent<TransformInit>(COMLAYER_FIRST);

        AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetUnlitShader();

        AddComponent<MatrixComponent>(COMLAYER_MATRIX)->SetIs2D();

        auto* uifc = AddComponent< UserInterfaceComponent>(COMLAYER_DRAW);
        uifc->LoadTexture("asset\\texture\\UI_Ling.png");
        //  uifc->SetDeployIndex(DEPLOY_LEFTUP);
        uifc->SetWidthHeight({ 50.0f,50.0f ,0.0f});
        uifc->SetIsChangeVertex();

        AddComponent<ImGuiComponent>(COMLAYER_SECOND)->SetIs2D();

        AddComponent<VertexChangeComponent>(COMLAYER_CHANGEVERTEX);

        ComponentObject::Init();
    }

};

