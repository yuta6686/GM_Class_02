#pragma once
#include "component_object.h"
#include "ModelColorChangeComponent_Titlebg.h"
#include "blink_component.h"
#include "gameObject.h"
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

        AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetShaderType(SHADER_UNLIT);

        AddComponent<MatrixComponent>(COMLAYER_MATRIX);

        auto* mdc = AddComponent<ModelDrawComponent>(COMLAYER_DRAW);
        mdc->SetSourcePath("asset\\model\\title_back_object.obj");
        mdc->SetIsVariable(true);
        

        AddComponent< ModelColorChangeComponent_Titlebg>(COMLAYER_SECOND);

        AddComponent<BlinkComponent>(COMLAYER_SECOND)->
            SetParameter(0.01f, 15.0f, 20.0f);
        

        ComponentObject::Init();
        mdc->SetDiffuse({ 0.0f,0.0f,0.0f,0.0f });
    }

    virtual void Update()override
    {
        float blink = GetComponent<BlinkComponent>()->GetBlinkValue();
        m_Scale.x = blink;
        m_Scale.y = blink;
        m_Scale.z = blink;

        if (m_Rotation.x >= 360.0f) {
            m_Rotation.x = 0.0f;
        }
        m_Rotation.x += 0.1f;

        ComponentObject::Update();
    }
};

