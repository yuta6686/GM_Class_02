#pragma once
#include "component.h"
//  ---------------------------------------------------------
//  BlinkComponent [BlinkComponent.h]
//                                  Author: Yanagisawa Yuta
//                                  Date  : 2022/07/30
//  ------------------------summary--------------------------
//  �_�ŃR���|�[�l���g�̃C���^�t�F�[�X
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
    /// �_�łɎg�p����ϐ����̐ݒ�
    /// </summary>
    /// <param name="speed">�_�ő��x</param>
    /// <param name="min">�_�ōŏ��l</param>
    /// <param name="max">�_�ōő�l</param>
    void SetParameter(float speed, float min, float max, AXIS axis = AXIS::AXIS_Y)
    {
        _param._speed = speed;
        _param._min = min;
        _param._max = max;
        _param._axis = axis;
        _param._blinkValue = 0.0f;
    }

    /// <summary>
    /// �_�ŏ��̎擾
    /// </summary>
    /// <returns></returns>
    float GetBlinkValue() { return _param._blinkValue; }

    BlinkParameter GetBlinkParameter()const { return _param; }
    void SetBlinkParameter(const BlinkParameter& param) { _param = param; }
};

