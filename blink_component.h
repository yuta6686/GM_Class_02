#pragma once
#include "component.h"
//  ---------------------------------------------------------
//  BlinkComponent [BlinkComponent.h]
//                                  Author: Yanagisawa Yuta
//                                  Date  : 2022/07/30
//  ------------------------summary--------------------------
//  点滅コンポーネントのインタフェース
//  ---------------------------------------------------------
class BlinkComponent :
    public Component
{
protected:
    float m_BlinkValue = 0.0f;
    float m_Work = 0.0f;

    float m_Speed = 0.01f;
    float m_Min = 0.3f;
    float m_Max = 0.5f;

    AXIS _axis = AXIS::AXIS_Y;
public:    
    virtual void Init() override {};

    virtual void Uninit() override {};

    virtual void Update() override;

    virtual void Draw() override {};

    virtual void DrawImgui() override;

    /// <summary>
    /// 点滅に使用する変数情報の設定
    /// </summary>
    /// <param name="speed">点滅速度</param>
    /// <param name="min">点滅最小値</param>
    /// <param name="max">点滅最大値</param>
    void SetParameter(float speed, float min, float max, AXIS axis = AXIS::AXIS_Y)
    {
        m_Speed = speed;
        m_Min = min;
        m_Max = max;
        _axis = axis;
    }

    /// <summary>
    /// 点滅情報の取得
    /// </summary>
    /// <returns></returns>
    float GetBlinkValue() { return m_BlinkValue; }
};

