#pragma once
#include "gameObject.h"
#include "ComponentObject.h"
class RenderingTexture :
    public ComponentObject
{
private:

public:
    // GameObject ����Čp������܂���
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

};

