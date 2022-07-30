#pragma once
#include "main.h"
#include "Resource.h"
#include "Enemy_Interface.h"

class Enemy : public Enemy_Interface
{

public:
    virtual void Init() {
        

        AddComponent<TransformInit>(COMLAYER_FIRST);

        AddComponent<ShaderComponent>(COMLAYER_SHADER);

        AddComponent<MatrixComponent>(COMLAYER_MATRIX);

        ModelDrawComponent* mdc =
            new ModelDrawComponent("asset\\model\\stone_white.obj");

        AddComponent(mdc, COMLAYER_DRAW);

        AddComponent< ImGuiComponent>(COMLAYER_SECOND)->SetEnemyVersion();

        SetHp(GetMaxHp());        

        ComponentObject::Init();
    }
};
