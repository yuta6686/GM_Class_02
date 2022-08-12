#pragma once
#include "Component.h"
#include "CountComponent.h"
#include "JumpComponent.h"

#include "manager.h"

class Enemy;
class MonochromeComponent :
	public Component
{
private:
	std::shared_ptr<Scene> m_Scene;
	CountComponent* m_Count;

	bool m_In = false;
	int m_BulletNum;

	VALIABLE m_Valiable = { 0.0f,1.0f,1.0f,1.0f };
	std::vector<VelocityComponent*> m_VelocityComponents;
	std::vector<Enemy*> m_Enemys;
public:
	void SetBulletNum(const int& bulletnum) { m_BulletNum = bulletnum; }

	virtual void Init() override;

	virtual void Uninit() override;

	virtual void Update() override;

	virtual void Draw() override;

	virtual void DrawImgui() override;

};

