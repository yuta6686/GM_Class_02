#pragma once
#include "ComponentObject.h"
#include "AnimationModelComponent.h"
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
            ->SetSourcePath("asset\\model\\Akai_Idle.fbx");

        ComponentObject::Init();

        float scale = 0.01f;
        m_Scale = { scale,scale,scale };

        m_Position.y = 4.0f;
    }
};

