#pragma once
#include "Component.h"
#include "gameObject.h"
class ImGuiComponent :
    public Component
{
private:
    inline static const float POSITION_MIN = -100.0f;    
    inline static const float POSITION_MAX = 100.0f;

    inline static const float ROTATION_MIN = -D3DX_PI;
    inline static const float ROTATION_MAX = D3DX_PI;

    inline static const float SCALE_MIN = 0.2f;
    inline static const float SCALE_MAX = 5.0f;
public:
    // Component を介して継承されました
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

};

