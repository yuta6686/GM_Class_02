#pragma once
#include "Component.h"

class MatrixComponent :
    public Component
{
private:
    bool m_Is2D = false;
public:


    // Component を介して継承されました
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual void DrawImgui()  override {};

    void SetIs2D(bool flag = true) {
        m_Is2D = flag;
    }
};

