#pragma once
#include "Component.h"

class MatrixComponent :
    public Component
{
public:


    // Component ����Čp������܂���
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

};

