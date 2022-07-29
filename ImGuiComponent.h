#pragma once
#include "Component.h"
#include "gameObject.h"
class ImGuiComponent :
    public Component
{
private:
    bool m_Is2D = false;

    inline static const float POSITION_MIN = -20.0f;    
    inline static const float POSITION_MAX = 20.0f;

    inline static const float POSITION_MIN_2D = 0.0f;
    inline static const float POSITION_MAX_X_2D = SCREEN_WIDTH;
    inline static const float POSITION_MAX_Y_2D = SCREEN_HEIGHT;

    inline static const float ROTATION_MIN = -D3DX_PI;
    inline static const float ROTATION_MAX = D3DX_PI;

    inline static const float SCALE_MIN = 0.2f;
    inline static const float SCALE_MAX = 5.0f;
public:
    // Component ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    void DrawImgui() override;

    void SetIs2D(const bool& flag = true)
    {
        m_Is2D = flag;
    }
};

