#pragma once
#include "Component.h"
#include "gameObject.h"
class ModelColorChangeComponent :
    public Component
{
private:
    D3DXCOLOR m_Diffuse = { 1.0f,1.0f,0.5f,1.0f };
public:

    virtual void Init() override;
    virtual void Uninit() override;
    virtual void Update() override;
    virtual void Draw() override;
    virtual void DrawImgui() override;
};

