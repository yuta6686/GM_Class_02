#pragma once
#include "BlinkComponent.h"
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
    virtual void Init()override {
        m_Scale = m_Parent->GetScale();
    }
    virtual void Update()override 
    {
        BlinkComponent::Update();

        if (m_IsX) {
            m_Scale.x = m_BlinkValue;
        }

        if (m_IsY) {
            m_Scale.y = m_BlinkValue;
        }

        if (m_IsZ) {
            m_Scale.z = m_BlinkValue;
        }
        m_Parent->SetScale(m_Scale);
    }

    virtual void SetParameter(const int& axis,
        const float& speed, const float& min, const float& max)
    {
        switch (axis)
        {
        case AXIS_X:
            m_IsX = true;
            break;
        case AXIS_Y:
            m_IsY = true;
            break;
        case AXIS_Z:
            m_IsZ = true;
            break;
        case AXIS_XY:
            m_IsX = true;
            m_IsY = true;
            break;
        case AXIS_XZ:
            m_IsX = true;
            m_IsZ = true;
            break;
        case AXIS_YZ:
            m_IsY = true;
            m_IsZ = true;
            break;
        case AXIS_XYZ:
        default:
            m_IsX = true;
            m_IsY = true;
            m_IsZ = true;
            break;               
        }
        BlinkComponent::SetParameter(speed, min, max);
    }
};

