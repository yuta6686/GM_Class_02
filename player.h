#pragma once

#include "main.h"
#include "model.h"
#include "gameObject_Invoke.h"
#include "component_object.h"
#include "player_rotate_component.h"
#include "shoot_bullet_component.h"
#include "monochrome_component.h"
#include "VelocityComponent.h"
#include "jump_component.h"
#include "ParticleObject.h"

class Audio;
class Shadow;


class Player :public ComponentObject
{
private:

	/// <summary>
	/// m_CameraRot
	/// ~~~~~~~~~~~
	/// プレイヤーのX軸を回転させたくない。
	/// カメラの角度を保持。
	/// 
	/// m_RotationにはX軸=0が入っている。
	/// </summary>	

	//D3DXVECTOR3 m_PlayerRotation;
	//D3DXVECTOR3 m_TargetRotation;

	class Audio* m_ShotSE;	
	class Audio* m_SEJump;
	class Audio* m_SELanding;
	class ShootBullet* m_ShootBullet;

	inline static const float GRAVITY = 0.01f;
	inline static const D3DXVECTOR3 ATTENUATION = { 0.9f,0.99f,0.9f };

	bool m_IsUseBullet = false;	
	inline static const float JUMP = 0.6f;

	bool m_IsNoMove = false;

	VelocityComponent* m_VelocityCom;	
	ParticleObject* m_Particle;
	D3DXCOLOR m_Color = { 1.0f,1.0f,1.0f,1.0f };
public:
	static float GetGravity() { return GRAVITY; }
	
	void Init()	 override;	
	void Update()override;
	void Draw()override;
	void DrawImgui() override;

	D3DXVECTOR3 GetCameraRot() { 

		return GetComponent<PlayerRotateComponent>()->m_CameraRot;
	}
	D3DXVECTOR3 GetCameraForward()
	{
		D3DXMATRIX rot;
		D3DXVECTOR3 crot = GetComponent<PlayerRotateComponent>()->m_CameraRot;
		D3DXMatrixRotationYawPitchRoll(&rot,
			crot.y, crot.x, crot.z);

		D3DXVECTOR3 forward;
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;

		return forward;
	}

	Audio* GetShootSE() { return m_ShotSE; }

	void SetIsUseBullet(bool flag = true) {
		ShootBulletComponent* sbc = GetComponent<ShootBulletComponent>();

		if (sbc)
			sbc->SetIsUseBullet(!flag);
		m_IsUseBullet = flag;
	}

	void SetIsNoMove(bool flag = true)
	{
		m_IsNoMove = flag;
	}

private:
	//	private変数

	//	private関数
	void PlayerMove();	
	void GetItem();	
	void SetParticle(const D3DXCOLOR& start_col);
	void SetParticle_Landing();

};