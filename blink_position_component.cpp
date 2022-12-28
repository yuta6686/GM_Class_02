#include "stdafx.h"
#include "blink_position_component.h"

void BlinkPositionComponent::SetInitPositionOnce()
{
	if (_isOnce)return;
	_initPosition = m_Parent->GetPosition();
	_isOnce = true;
}

void BlinkPositionComponent::Update()
{
	// e‚ÌˆÊ’uŽæ“¾
	SetInitPositionOnce();

	D3DXVECTOR3 blinkPos = _initPosition;
	switch (_axis)
	{
	case AXIS_X:
		blinkPos.x += m_BlinkValue;
		break;
	case AXIS_Y:
		blinkPos.y += m_BlinkValue;
		break;
	case AXIS_Z:
		blinkPos.z += m_BlinkValue;
		break;
	case AXIS_XY:
		blinkPos.x += m_BlinkValue;
		blinkPos.y += m_BlinkValue;
		break;
	case AXIS_XZ:
		blinkPos.x += m_BlinkValue;
		blinkPos.z += m_BlinkValue;
		break;
	case AXIS_YZ:
		blinkPos.y += m_BlinkValue;
		blinkPos.z += m_BlinkValue;
		break;
	case AXIS_XYZ:
		blinkPos.x += m_BlinkValue;
		blinkPos.y += m_BlinkValue;
		blinkPos.z += m_BlinkValue;
		break;
	default:
		break;
	}

	m_Parent->SetPosition(blinkPos);

	BlinkComponent::Update();
}

