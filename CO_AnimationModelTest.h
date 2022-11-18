#pragma once
#include "ComponentObject.h"
#include "animation_model_component.h"
class CO_AnimationModelTest :
    public ComponentObject
{
public:
    virtual void Init()override
    {
        AddComponent<TransformInit>(COMLAYER_FIRST);

        AddComponent<ShaderComponent>(COMLAYER_SHADER);

        AddComponent<MatrixComponent>(COMLAYER_MATRIX);

        AddComponent< AnimationModelComponent>(COMLAYER_DRAW)
            ->LoadAnimationData("asset\\model\\BlenderTest3.fbx",
                "asset\\model\\BlenderTest3.fbx", "Idle",
                "asset\\model\\BlenderTest3.fbx", "Run");

        AddComponent<ImGuiComponent>(COMLAYER_DRAW);

        ComponentObject::Init();

        m_TypeName = "AnimationModel";

        float scale = 1.1f;
        m_Scale = { scale,scale,scale };

        m_Position.y = 4.0f;
    }
};

