#pragma once
/** ---------------------------------------------------------
///  GravityComponent [gravity_component.h]
///                                  @author: yanagisaya.yuta
///                                  @date  : 2022/11/21
///  ------------------------summary--------------------------
///  * @brief  重力コンポーネント
///  ---------------------------------------------------------*/
#include "component.h"
#include "main.h"

class VelocityComponent;
class GravityComponent :
	public Component
{
private:
	std::vector<VelocityComponent*> m_Velocity;
public:
	virtual void Init() override;
	virtual void Uninit() override {}
	virtual void Update() override;
	virtual void Draw() override {}
	virtual void DrawImgui() override {}
};
