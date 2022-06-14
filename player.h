#pragma once
#include "main.h"
#include "model.h"
#include "gameObject.h"


class Player:public GameObject
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

	//	後で他のクラスに標準化する
	float GetRadian(float degree) { return degree * (D3DX_PI / 180.0f); }
	D3DXVECTOR3 GetRadian(D3DXVECTOR3 degree) { return degree * (D3DX_PI / 180.0f); }
	D3DXVECTOR3 GetDegree(D3DXVECTOR3 radian) { return radian * (180.0f / D3DX_PI); }
	
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
	void ShootBullet();
};

