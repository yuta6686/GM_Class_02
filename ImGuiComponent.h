#pragma once
#include "Component.h"
#include "gameObject.h"
class ImGuiComponent :
    public Component
{
protected:
    bool m_Is2D = false;
    bool m_IsEnemyVersion = false;
    bool m_IsUse = false;

    float POSITION_MIN = -20.0f;    
    float POSITION_MAX = 20.0f;

    float POSITION_MIN_2D = 0.0f;
    float POSITION_MAX_X_2D = SCREEN_WIDTH;
    float POSITION_MAX_Y_2D = SCREEN_HEIGHT;

    float ROTATION_MIN = -D3DX_PI;
    float ROTATION_MAX = D3DX_PI;

    float SCALE_MIN = 0.2f;
    float SCALE_MAX = 5.0f;

    int m_ImVecY = 400;
public:
    // Component を介して継承されました
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    void DrawImgui() override;

    void SetIs2D(const bool& flag = true)
    {
        m_Is2D = flag;
    }

    void SetEnemyVersion() 
    {
        m_IsEnemyVersion = true;

        POSITION_MIN = -200.0f;
        POSITION_MAX = 200.0f;

        ROTATION_MIN = -D3DX_PI;
        ROTATION_MAX = D3DX_PI;

        SCALE_MIN = 0.2f;
        SCALE_MAX = 5.0f;

        m_ImVecY = 700;
    }

    bool GetIsUse()const { return m_IsUse; }
    void SetIsUse(const bool& flag) { m_IsUse = flag; }  
    
};

