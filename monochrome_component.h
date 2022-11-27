#pragma once
/** ---------------------------------------------------------
 *  MonochromeComponent [monochrome_component.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2022/11/21
 * ------------------------summary--------------------------
 * @brief  左クリック押下中、画面全体モノクロ化
 ** ---------------------------------------------------------*/
#include "component.h"

#include "gameObject.h"

class Enemy;
class ShootBullet;
class VelocityComponent;
class CountComponent;
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
	std::vector<GameObject*> m_Enemys;
	ShootBullet* m_ShootBullet;
public:
	void SetBulletNum(const int& bulletnum) { m_BulletNum = bulletnum; }

	virtual void Init() override;

	virtual void Uninit() override;

	virtual void Update() override;

	virtual void Draw() override;

	virtual void DrawImgui() override;

};

