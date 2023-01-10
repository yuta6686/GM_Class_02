#pragma once
/** ---------------------------------------------------------
 *  RandomVelocityComponent [random_velocity_component.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2022/11/21
 * ------------------------summary--------------------------
 * @brief  ƒ‰ƒ“ƒ_ƒ€‚Å“®‚­
 *
 ** ---------------------------------------------------------*/

#include "component.h"
#include "velocity_component.h"
class RandomVelocityComponent :
	public Component
{
private:
	float m_Speed = 1.0f;

	D3DXVECTOR3 m_RandomVector = { 1.0f,1.0f,1.0f };

	std::vector<VelocityComponent*> m_Velocities;
public:
	void SetSpeed(const float& speed)
	{
		m_Speed = speed;
	}

	virtual void Init() override;

	virtual void Uninit() override {};
	virtual void Update() override {};
	virtual void Draw() override {};
	virtual void DrawImgui() override {};
};
