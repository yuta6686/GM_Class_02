#pragma once
/** ---------------------------------------------------------
 *  AlphaBlink2DComponent [blink_alpha2d_component.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2022/11/21
 * ------------------------summary--------------------------
 * @brief  2Dì_ñ≈èàóù
 ** ---------------------------------------------------------*/
#include "component.h"
#include "blink_component.h"

class AlphaBlink2DComponent :
	public BlinkComponent
{
private:
	class UserInterfaceComponent* _uiComponent = nullptr;
public:
	virtual void Init() override;

	virtual void Update() override;
};

