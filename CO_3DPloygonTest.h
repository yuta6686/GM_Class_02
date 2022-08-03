#pragma once
#include "ComponentObject.h"
#include "Polygon3DComponent.h"
#include "VertexChangerComponent_Color.h"
class CO_3DPloygonTest :
    public ComponentObject
{
public:
    virtual void Init()override {
        AddComponent<TransformInit>(COMLAYER_FIRST)->
            SetInitScale({ 2.5f,4.0f,1.0f });

        AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetUnlitShader();

        AddComponent<MatrixComponent>(COMLAYER_MATRIX)->SetIsBillboard();

        auto* pol3d = AddComponent<Polygon3DComponent>(COMLAYER_DRAW);
        pol3d->LoadTexture("asset\\texture\\rect.png");
        pol3d->SetIsChangeVertex();
        pol3d->SetIsUseAlphaToCoverage();

        AddComponent< VertexChangerComponent_Color>(COMLAYER_CHANGEVERTEX);

        ComponentObject::Init();
    }
};

