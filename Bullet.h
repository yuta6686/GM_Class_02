#pragma once
#include "main.h"
#include "gameobject.h"

class Bullet : public GameObject
{
private:
	static class Model* m_Model;

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;

	inline const static float BULLET_SPEED_MAX = 1.0f;
public:
	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();

};

