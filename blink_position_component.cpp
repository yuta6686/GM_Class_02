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
	switch (_param._axis)
	{
	case AXIS_X:
		blinkPos.x += _param._blinkValue;
		break;
	case AXIS_Y:
		blinkPos.y += _param._blinkValue;
		break;
	case AXIS_Z:
		blinkPos.z += _param._blinkValue;
		break;
	case AXIS_XY:
		blinkPos.x += _param._blinkValue;
		blinkPos.y += _param._blinkValue;
		break;
	case AXIS_XZ:
		blinkPos.x += _param._blinkValue;
		blinkPos.z += _param._blinkValue;
		break;
	case AXIS_YZ:
		blinkPos.y += _param._blinkValue;
		blinkPos.z += _param._blinkValue;
		break;
	case AXIS_XYZ:
		blinkPos.x += _param._blinkValue;
		blinkPos.y += _param._blinkValue;
		blinkPos.z += _param._blinkValue;
		break;
	default:
		break;
	}

	m_Parent->SetPosition(blinkPos);

	BlinkComponent::Update();
}

