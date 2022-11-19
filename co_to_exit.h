#pragma once
#include "component_object.h"
#include "ModelColorChangeComponent_Titlebg.h"
#include "blink_scale_component.h"
class CO_toExit :
    public ComponentObject
{
public:
    virtual void Init()override
    {
        const float scale = 5.0f;
        auto* init = AddComponent<TransformInit>(COMLAYER_FIRST);
        init->SetInitScale({ scale,scale,scale });


        AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetShaderType(SHADER_UNLIT);

        AddComponent<MatrixComponent>(COMLAYER_MATRIX);

        auto* mdc = AddComponent<ModelDrawComponent>(COMLAYER_DRAW);
        mdc->SetSourcePath("asset\\model\\exit.obj");
        mdc->SetIsVariable(true);

        AddComponent< ModelColorChangeComponent_Titlebg>(COMLAYER_SECOND);

        AddComponent< BlinkComponent_Scale>(COMLAYER_SECOND)
            ->SetParameter(AXIS_XYZ, 0.05f, 7.5f, 10.0f);

        AddComponent<ImGuiComponent>(COMLAYER_SECOND);


        ComponentObject::Init();
        mdc->SetDiffuse({ 1.0f,1.0f,1.0f,1.0f });
    }
};

