#pragma once
#include "ComponentObject.h"

#include "ModelColorChangeComponent.h"

class ComponentObjectTest :
    public ComponentObject
{
public:
    virtual void Init() {      
        m_TypeName = "ComponentObjectTest";

        AddComponent<TransformInit>(COMLAYER_FIRST);

        AddComponent<ShaderComponent>(COMLAYER_SHADER);

        AddComponent<MatrixComponent>(COMLAYER_MATRIX);                   

        auto* mdc =AddComponent<ModelDrawComponent>(COMLAYER_DRAW);
        mdc->SetSourcePath("asset\\model\\cylinder.obj");
        mdc->SetIsVariable(true);               

        //AddComponent(mdc, COMLAYER_DRAW);


        AddComponent< ModelColorChangeComponent>(COMLAYER_SECOND);

        AddComponent< ImGuiComponent>(COMLAYER_SECOND);
        

        ComponentObject::Init();
        
    }
};

