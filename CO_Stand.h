#pragma once
#include "component_object.h"
#include "texture_compoennt.h"
class CO_Stand :
    public ComponentObject
{
public:
    virtual void Init()override
    {
        AddComponent<TransformInit>(COMLAYER_FIRST)
            ->SetInitPosScale({ 2.5f,0.1f,0.0f }, { 5.0f,5.0f,5.0f });

        AddComponent<TextureComponent>(COMLAYER_DRAW)->
            SetTextureAndSlot("asset\\texture\\normalmap.dds",1);
        

        AddComponent<ShaderComponent>(COMLAYER_SHADER);

        AddComponent<MatrixComponent>(COMLAYER_MATRIX);

        AddComponent<ModelDrawComponent>(COMLAYER_DRAW)->
            SetSourcePath("asset\\model\\stand.obj");

        ComponentObject::Init();
    }
};

