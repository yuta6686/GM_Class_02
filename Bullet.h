#pragma once
#include "main.h"
#include "gameobject.h"

class Bullet : public GameObject
{
private:
	static inline const float BULLET_SPEED_MAX = 5.0f;
	static inline float m_Speed = 1.0f;
	static inline std::shared_ptr<Resource> m_Model;

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;

	D3DXVECTOR3 m_Forward;
public:		
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetForward(D3DXVECTOR3 vec) {
		m_Forward = vec;
	}

	void SetSpeed(const float& speed) {
		m_Speed = speed;
	}
};

