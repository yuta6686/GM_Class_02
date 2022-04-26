#pragma once


class Camera
{
private :
	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_Target;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

