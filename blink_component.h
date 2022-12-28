#pragma once
#include "component.h"
//  ---------------------------------------------------------
//  BlinkComponent [BlinkComponent.h]
//                                  Author: Yanagisawa Yuta
//                                  Date  : 2022/07/30
//  ------------------------summary--------------------------
//  点滅コンポーネントのインタフェース
//  ---------------------------------------------------------
struct BlinkParameter 
{
    float _blinkValue = 0.0f;
    float _work = 0.0f;

    float _speed = 0.01f;
    float _min = 0.3f;
    float _max = 0.5f;

    AXIS _axis = AXIS::AXIS_Y;
};
class BlinkComponent :
    public Component
{
protected:

    BlinkParameter _param;
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
        _param._speed = speed;
        _param._min = min;
        _param._max = max;
        _param._axis = axis;
        _param._blinkValue = 0.0f;
    }

    /// <summary>
    /// 点滅情報の取得
    /// </summary>
    /// <returns></returns>
    float GetBlinkValue() { return _param._blinkValue; }

    BlinkParameter GetBlinkParameter()const { return _param; }
    void SetBlinkParameter(const BlinkParameter& param) { _param = param; }
};

