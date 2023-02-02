#include "blink_component.h"
#include "gameObject.h"

void BlinkComponent::Update()
{
	_param._work += _param._speed;

	if (_param._work > D3DX_PI * 2.0f) {
		_param._work = 0.0f;
	}

	_param._blinkValue = (sinf(_param._work) + 1.0f) / (2.0f) * (_param._max - _param._min) + _param._min;
}

void BlinkComponent::DrawImgui()
{
	ImGui::SliderFloat("Speed", &_param._speed, 0.0f, 1.0f);
	ImGui::SliderFloat("Min", &_param._min, -1.0f, 1.0f);
	ImGui::SliderFloat("Max", &_param._max, -1.0f, 1.0f);
	ImGui::SliderFloat("work", &_param._blinkValue, _param._min, _param._max);
}
