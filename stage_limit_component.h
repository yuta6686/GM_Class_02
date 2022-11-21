#pragma once
/** ---------------------------------------------------------
 *  StageLimitComponent [stage_limit_component.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2022/11/21
 * ------------------------summary--------------------------
 * @brief  �X�e�[�W�̌��E�l�ɗ�����A�x���V�e�B��0�ɂ���
 * 
 ** ---------------------------------------------------------*/
#include "component.h"
#include "velocity_component.h"

class StageLimitComponent :
	public Component
{
protected:
	std::vector<VelocityComponent*> m_Velocities;

	inline static const float X_MAX = 23.5f;
	inline static const float X_MIN = -19.5f;

	inline static const float Y_MAX = 100.0f;
	//  �������̌��E�͑��ł���Ă�̂ł��Ȃ�

	inline static const float Z_MAX = 42.0f;
	inline static const float Z_MIN = -37.5f;
public:

	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;

	virtual void DrawImgui() override;
};
