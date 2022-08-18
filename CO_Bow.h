#pragma once
#include "ComponentObject.h"
class CO_Bow :
    public ComponentObject
{
public:
    virtual void Init()override
    {
        AddComponent<TransformInit>(COMLAYER_FIRST);

        AddComponent<ShaderComponent>(COMLAYER_SHADER);

        AddComponent<MatrixComponent>(COMLAYER_MATRIX);

        auto* mdc = AddComponent<ModelDrawComponent>(COMLAYER_DRAW);
        mdc->SetSourcePath("asset\\model\\bow_red.obj");

        ComponentObject::Init();

        m_Position.z = 50.0f;
        m_Position.y = 20.0f;

        m_Rotation.x = MyMath::GetRadian(90.0f);

        m_Scale *= 25.0f;
    }
};

