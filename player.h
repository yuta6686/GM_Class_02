#pragma once
#include "main.h"
#include "model.h"
#include "gameObject_Invoke.h"
#include "ComponentObject.h"
#include "PlayerRotateComponent.h"

class Audio;
class Shadow;
class ShootBullet;



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
	D3DXVECTOR3 m_Velocity;	//	速度

	//D3DXVECTOR3 m_PlayerRotation;
	//D3DXVECTOR3 m_TargetRotation;

	class Audio* m_ShotSE;
	class Shadow* m_Shadow;
	class ShootBullet* m_ShootBullet;

	//	後で他のクラスに標準化する
	float GetRadian(float degree) { return degree * (D3DX_PI / 180.0f); }
	D3DXVECTOR3 GetRadian(D3DXVECTOR3 degree) { return degree * (D3DX_PI / 180.0f); }
	D3DXVECTOR3 GetDegree(D3DXVECTOR3 radian) { return radian * (180.0f / D3DX_PI); }

	inline static const float GRAVITY = 0.01f;
	inline static const float JUMP = 0.3f;
	inline static const D3DXVECTOR3 ATTENUATION = { 0.9f,0.99f,0.9f };

	bool m_IsUseBullet = true;


	bool m_IsNoMove = false;
public:
	void Init()	 override;
	void Uninit()override;
	void Update()override;
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
	void PlayerRotation();
	void GetItem();
	void ShootBulletFunc();

};