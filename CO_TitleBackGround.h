#pragma once
#include "ComponentObject.h"
#include "ModelColorChangeComponent_Titlebg.h"
class CO_TitleBackGround :
    public ComponentObject
{
public:
    virtual void Init()override
    {
        const float scale = 20.0f;
        auto* init = AddComponent<TransformInit>(COMLAYER_FIRST);
            init->SetInitScale({ scale,scale,scale });
            init->SetInitPosition({ 0.0f,1.75f,0.0f });

        AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetUnlitShader();

        AddComponent<MatrixComponent>(COMLAYER_MATRIX);

        auto* mdc = AddComponent<ModelDrawComponent>(COMLAYER_DRAW);
        mdc->SetSourcePath("asset\\model\\title_back_object.obj");
        mdc->SetIsVariable(true);
        

        AddComponent< ModelColorChangeComponent_Titlebg>(COMLAYER_SECOND);
        

        ComponentObject::Init();
        mdc->SetDiffuse({ 0.0f,0.0f,0.0f,0.0f });
    }
};

