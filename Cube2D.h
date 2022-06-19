#pragma once
#include "gameObject.h"
class Scene;
class Cube2D :
    public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	//ID3D11ShaderResourceView*	m_Texture = NULL;
	std::shared_ptr<Resource> m_Texture;

	std::shared_ptr<VertexShader> m_VertexShader;
	std::shared_ptr<PixelShader> m_PixelShader;

	D3DXVECTOR3 m_Speed;
	D3DXVECTOR3 m_Offset = { SCREEN_WIDTH / 2.0f,SCREEN_HEIGHT / 2.0f,0.0f };

	int m_Index;
	inline static int s_Index = 0;

	Scene* m_Scene;
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void SetSpeed(const D3DXVECTOR3& speed) 
	{
		m_Speed = speed;
	}

	void SetPosition(D3DXVECTOR3 pos)override {
		GameObject::SetPosition(pos + m_Offset);		
	}

	int GetIndex() { return m_Index; }
};

