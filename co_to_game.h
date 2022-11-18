#pragma once
//  ---------------------------------------------------------
//  CO_toGame [co_to_game.h]
//                                  Author: YanagisawaYuta
//                                  Date  : 2022/09/05
//  ------------------------summary--------------------------
//  - Titleシーンのオブジェクト
//  ---------------------------------------------------------
#include "component_object.h"
#include "ModelColorChangeComponent_Titlebg.h"
#include "blink_scale_component.h"
class CO_toGame :
    public ComponentObject
{
public:
    virtual void Init()override
    {
        const float scale = 2.5f;
        auto* init = AddComponent<TransformInit>(COMLAYER_FIRST);
        init->SetInitScale({ scale,scale,scale });


        AddComponent<ShaderComponent>(COMLAYER_SHADER)->SetUnlitShader();

        AddComponent<MatrixComponent>(COMLAYER_MATRIX);

        auto* mdc = AddComponent<ModelDrawComponent>(COMLAYER_DRAW);
        mdc->SetSourcePath("asset\\model\\toGame.obj");
        mdc->SetIsVariable(true);

        AddComponent< ModelColorChangeComponent_Titlebg>(COMLAYER_SECOND);

        AddComponent< BlinkComponent_Scale>(COMLAYER_SECOND)
            ->SetParameter(AXIS_XYZ, 0.05f, 2.5f, 3.0f);

        AddComponent<ImGuiComponent>(COMLAYER_SECOND);


        ComponentObject::Init();
        mdc->SetDiffuse({ 1.0f,1.0f,1.0f,1.0f });
    }
};

