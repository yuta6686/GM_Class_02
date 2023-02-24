#pragma once
#include "Component.h"
class ShaderResourceViewComponent :
    public Component
{
    UINT _slot = 0;
    ShaderResourceView _srv = nullptr;
    bool _renderingTexture = false;
public:
    
    virtual void Init() override;
    virtual void Uninit() override;
    virtual void Update() override;
    virtual void Draw() override;
    virtual void DrawImgui() override;

    void SetSRV(UINT slot, ShaderResourceView srv);
    void SetRenderingTexture(UINT slot);
};

