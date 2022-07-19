#pragma once
#include "Component.h"

class MatrixComponent :
    public Component
{
public:


    // Component を介して継承されました
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

};

