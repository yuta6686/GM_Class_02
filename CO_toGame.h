#pragma once
#include "ComponentObject.h"
#include "ModelColorChangeComponent_Titlebg.h"
#include "BlinkComponent_Scale.h"
class CO_toGame :
    public ComponentObject
{
public:
    virtual void Init()override
    {
        const float scale = 5.0f;
        auto* init = AddComponent<TransformInit>(COMLAYER_FIRST);
        init->SetInitScale({ scale,scale,scale });


        AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetUnlitShader();

        AddComponent<MatrixComponent>(COMLAYER_MATRIX);

        auto* mdc = AddComponent<ModelDrawComponent>(COMLAYER_DRAW);
        mdc->SetSourcePath("asset\\model\\toGame.obj");
        mdc->SetIsVariable(true);

        AddComponent< ModelColorChangeComponent_Titlebg>(COMLAYER_SECOND);

        AddComponent< BlinkComponent_Scale>(COMLAYER_SECOND)
            ->SetParameter(AXIS_XYZ, 0.05f, 7.5f, 10.0f);

        AddComponent<ImGuiComponent>(COMLAYER_SECOND);


        ComponentObject::Init();
        mdc->SetDiffuse({ 1.0f,1.0f,1.0f,1.0f });
    }
};

