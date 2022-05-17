#pragma once
#include "gameObject.h"

class Camera :public GameObject
{
private :
	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_Target;

	Camera() = default;
	~Camera() = default;

	static Camera* m_Instance;
public:
	static Camera* Instance();

	void Init()		override;
	void Uninit()	override;
	void Update()	override;
	void Draw()		override;
};

