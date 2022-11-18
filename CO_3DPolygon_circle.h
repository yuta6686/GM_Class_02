#pragma once
#include "ComponentObject.h"
#include "polygon3d_component.h"
#include "VertexChangeComponent_ToGame.h"
class CO_3DPolygon_circle :
    public ComponentObject
{
public:
    virtual void Init()override
    {
        AddComponent<TransformInit>(COMLAYER_FIRST)->
            SetInitScale({ 1.0f,1.0f,1.0f });

        AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetUnlitShader();

        AddComponent<MatrixComponent>(COMLAYER_MATRIX);

        auto* pol3d = AddComponent<Polygon3DComponent>(COMLAYER_DRAW);
        pol3d->LoadTexture("asset\\texture\\circle_blue.png");
        pol3d->SetIsChangeVertex(true);
        pol3d->SetIsUseAlphaToCoverage(true);
        pol3d->SetIsVertical(false);
        pol3d->SetIsCullNone(true);               

        ComponentObject::Init();

    }
};

