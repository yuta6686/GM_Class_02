#pragma once
//  ---------------------------------------------------------
//  BlinkSomponent_Scale [blink_scale_component]
//                                  Author: ñˆ‡VóDëæ
//                                  Date  : 2022/11/21
//  ------------------------summary--------------------------
//  ì_ñ≈èàóù
//  ---------------------------------------------------------
#include "blink_component.h"
#include "gameObject.h"

enum AXIS
{
    AXIS_X,
    AXIS_Y,
    AXIS_Z,
    AXIS_XY,
    AXIS_XZ,
    AXIS_YZ,
    AXIS_XYZ
};

class BlinkComponent_Scale :
    public BlinkComponent
{
private:
    D3DXVECTOR3 m_Scale;
    bool m_IsX = false;
    bool m_IsY = false;
    bool m_IsZ = false;
public:    
    virtual void Init()override;
    virtual void Update()override;

    virtual void SetParameter(const int& axis,
        const float& speed, const float& min, const float& max);    
};

