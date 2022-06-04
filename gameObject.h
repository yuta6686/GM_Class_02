#pragma once
#include "main.h"
class GameObject
{
protected:
	bool m_Destroy = false;

	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_Rotation;
	D3DXVECTOR3 m_Scale;
public:
	virtual void Init()	 = 0;
	virtual void Uninit()= 0;
	virtual void Update()= 0;
	virtual void Draw()	 = 0;

	void SetPosition(D3DXVECTOR3 Position)
	{
		m_Position = Position;
	}
	D3DXVECTOR3 GetPosition() { return m_Position; }
	
	const D3DXVECTOR3& GetPositionReference()const 
	{
		return m_Position;
	}

	void SetDestroy() { m_Destroy = true; }

	bool Destroy()
	{
		if (m_Destroy)
		{
			Uninit();
			delete this;
			return true;
		}
		else
		{
			return false;
		}
	}
};

