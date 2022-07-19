#pragma once
#include "ComponentObject.h"

class ComponentObjectTest :
    public ComponentObject
{
public:
    virtual void Init() {        
        AddComponent<TransformInit>(COMLAYER_FIRST);

        AddComponent<ShaderComponent>(COMLAYER_SHADER);

        AddComponent<MatrixComponent>(COMLAYER_MATRIX);

        ModelDrawComponent* mdc = 
            new ModelDrawComponent("asset\\model\\cylinder.obj");

        AddComponent(mdc, COMLAYER_DRAW);
        

        ComponentObject::Init();
        
    }
};

