#pragma once
#include "gameObject.h"
class ComputeShaderTest2 :
    public GameObject
{
public:


    // GameObject ����Čp������܂���
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

};

