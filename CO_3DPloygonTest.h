#pragma once
#include "component_object.h"
#include "polygon3d_component.h"
#include "VertexChangeComponent_ToGame.h"
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
        pol3d->SetIsChangeVertex(true);
        pol3d->SetIsUseAlphaToCoverage(true);
        //  pol3d->SetIsCullNone(true);       

        AddComponent< VertexChangeComponent_ToGame>(COMLAYER_CHANGEVERTEX);

        ComponentObject::Init();
    }
};

