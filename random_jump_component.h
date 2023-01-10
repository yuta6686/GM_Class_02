#pragma once
/** ---------------------------------------------------------
 *  RandomJumpComponent [random_jump_component.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2022/11/21
 * ------------------------summary--------------------------
 * @brief  êîïbÇ≤Ç∆Ç…ìÆÇ≠
 ** ---------------------------------------------------------*/

#include "component.h"


class CountComponent;
class VelocityComponent;
class RandomJumpComponent :
	public Component
{
private: // const
	inline static const float ENEMY_JUMP_VALUE = 0.5f;
	inline static const int JUMP_INTERVAL = 180;

private: // member
	std::vector<VelocityComponent*> m_Velociy;
	CountComponent* m_Count;

public:
	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void DrawImgui() override;
};
