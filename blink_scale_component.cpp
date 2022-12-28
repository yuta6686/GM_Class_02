#include "blink_scale_component.h"

void BlinkComponent_Scale::Init() 
{
	m_Scale = m_Parent->GetScale();
}

void BlinkComponent_Scale::Update()
{
	BlinkComponent::Update();

	if (m_IsX) {
		m_Scale.x = _param._blinkValue;
	}

	if (m_IsY) {
		m_Scale.y = _param._blinkValue;
	}

	if (m_IsZ) {
		m_Scale.z = _param._blinkValue;
	}
	m_Parent->SetScale(m_Scale);
}
void BlinkComponent_Scale::SetParameter(const int& axis,
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