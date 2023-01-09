#pragma once
/** ---------------------------------------------------------
 *  [co_noise_circle.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2023/1/9
 * ------------------------summary--------------------------
 * @brief  円形のNoise柄？的なやつ
 * @link  https://yuta6686.atlassian.net/browse/AS-9
 * - 複数体共存は厳しいかも。
 * - Shaderで固定された値を使ってるので。
 ** ---------------------------------------------------------*/

#include "component_object.h"
class CO_NoiseCircle :
    public ComponentObject
{	
public:
	void InitInternal()override;
	void UninitInternal()override;
	void UpdateInternal()override;
	void DrawInternal()override;
	void DrawImguiInternal()override;
};

