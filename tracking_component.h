#pragma once
/** ---------------------------------------------------------
 *  TrackingComponent [tracking_component.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2022/11/21
 * ------------------------summary--------------------------
 * @brief  �v���C���[�Ɍ�������Velocity��������
 * @what   ��ɃG�l�~�[�Ŏg�p
 ** ---------------------------------------------------------*/
#include "component.h"
#include "gameObject.h"

class VelocityComponent;
class TrackingComponent :
	public Component
{
private:
	GameObject* m_Target;

	//  Velocity�R���|�[�l���g�Ƃ��Ď���
	VelocityComponent* m_VelocityComponent;

	float m_Speed = 0.1f;
public:
	void SetSpeed(const float& speed) { m_Speed = speed; }
	float GetSpeed()const { return m_Speed; }

	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void DrawImgui() override;
};
