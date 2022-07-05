#pragma once
#include "main.h"
#include "model.h"
#include "gameObject.h"
class Audio;
class Shadow;
class ShootBullet;

class Player:public GameObject
{
private:
	/// <summary>
	/// m_CameraRot
	/// ~~~~~~~~~~~
	/// �v���C���[��X������]���������Ȃ��B
	/// �J�����̊p�x��ێ��B
	/// 
	/// m_Rotation�ɂ�X��=0�������Ă���B
	/// </summary>
	D3DXVECTOR3 m_CameraRot;
	D3DXVECTOR3 m_Velocity;	//	���x

	class Audio* m_ShotSE;
	class Shadow* m_Shadow;
	class ShootBullet* m_ShootBullet;	

	//	��ő��̃N���X�ɕW��������
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
	//	private�ϐ�
	static inline std::shared_ptr<Resource> m_Model;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	//	private�֐�
	void PlayerMove();
	void PlayerRotation();
	void GetItem();
	void ShootBulletFunc();
};

