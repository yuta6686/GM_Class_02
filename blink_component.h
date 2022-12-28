#pragma once
#include "component.h"
//  ---------------------------------------------------------
//  BlinkComponent [BlinkComponent.h]
//                                  Author: Yanagisawa Yuta
//                                  Date  : 2022/07/30
//  ------------------------summary--------------------------
//  �_�ŃR���|�[�l���g�̃C���^�t�F�[�X
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
    /// �_�łɎg�p����ϐ����̐ݒ�
    /// </summary>
    /// <param name="speed">�_�ő��x</param>
    /// <param name="min">�_�ōŏ��l</param>
    /// <param name="max">�_�ōő�l</param>
    void SetParameter(float speed, float min, float max, AXIS axis = AXIS::AXIS_Y)
    {
        m_Speed = speed;
        m_Min = min;
        m_Max = max;
        _axis = axis;
    }

    /// <summary>
    /// �_�ŏ��̎擾
    /// </summary>
    /// <returns></returns>
    float GetBlinkValue() { return m_BlinkValue; }
};

