#pragma once
#include "gameObject.h"
class ComputeShaderTest2 :
    public GameObject
{
public:


    // GameObject を介して継承されました
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

};

