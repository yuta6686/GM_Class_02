#pragma once
#include "main.h"
#include "model.h"
#include "gameObject_Invoke.h"
#include <queue>
class Audio;
class Shadow;
class ShootBullet;



class Player :public GameObject
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
	D3DXVECTOR3 m_CameraRot;
	D3DXVECTOR3 m_Velocity;	//	速度

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



public:
	void Init()	 override;
	void Uninit()override;
	void Update()override;
	void Draw()	 override;

	D3DXVECTOR3 GetCameraRot() { return m_CameraRot; }
	D3DXVECTOR3 GetCameraForward()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot,
			m_CameraRot.y, m_CameraRot.x, m_CameraRot.z);

		D3DXVECTOR3 forward;
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;

		return forward;
	}

	Audio* GetShootSE() { return m_ShotSE; }
private:
	//	private変数
	static inline std::shared_ptr<Resource> m_Model;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	//	private関数
	void PlayerMove();
	void PlayerRotation();
	void GetItem();
	void ShootBulletFunc();
	void Move();

	std::vector<INVOKE> m_Invokes;

	
	typedef void(Player::* MAMBER_FUNC)();

	std::vector<MAMBER_FUNC> m_FuncList;

	template <class T>
	void Invoke(T(Player::* func)(), int delay) {
		m_FuncList.push_back(func);
		m_Invokes.push_back({ delay,0,true });		
	}

	//	m_DelayCount ,m_DelayCounterをqueueにして使う。
	void InvokeUpdate() {
		
		if (m_FuncList.empty() ||
			m_Invokes.empty())return;

		//	後ろから回す
		for (int i = m_Invokes.size() - 1; i >= 0; i--) {
			if (!m_Invokes[i].m_IsInvoke)continue;
			if (m_Invokes[i].m_DelayCounter < m_Invokes[i].m_DelayCountMax) {
				m_Invokes[i].m_DelayCounter++;
			}
			else {
				m_Invokes[i].m_DelayCounter = 0;
				m_Invokes[i].m_IsInvoke = false;
				(this->*m_FuncList[i])();

				m_Invokes.erase(m_Invokes.begin() + i);
				m_FuncList.erase(m_FuncList.begin() + i);

			}
		}
	}
};

