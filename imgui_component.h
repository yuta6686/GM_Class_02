//  ---------------------------------------------------------
//  ImGuiComponent [ImGuiComponent.h]
//                                  Author: YanagisawaYuta
//                                  Date  : 2022/09/06
//  ------------------------summary--------------------------
//  - Transform í≤êÆ
//  ---------------------------------------------------------
#pragma once

#include "component.h"
#include "gameObject.h"
class ImGuiComponent :
    public Component
{
protected:
    bool m_Is2D = false;
    bool m_IsEnemyVersion = false;
    bool m_IsUse = false;

    float POSITION_MIN = -50.0f;    
    float POSITION_MAX = 50.0f;

    float POSITION_MIN_2D = 0.0f;
    float POSITION_MAX_X_2D = SCREEN_WIDTH;
    float POSITION_MAX_Y_2D = SCREEN_HEIGHT;

    float ROTATION_MIN = 0.0f;
    float ROTATION_MAX = D3DX_PI * 2.0f;

    float SCALE_MIN = 0.0f;
    float SCALE_MAX = 200.0f;

    int m_ImVecY = 400;
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

    void SetEnemyVersion();

    bool GetIsUse()const { return m_IsUse; }
    void SetIsUse(const bool& flag) { m_IsUse = flag; }  
    
};

