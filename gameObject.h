#pragma once

#include "main.h"
#include "texture.h"
#include "vertexShader.h"
#include "pixelShader.h"

class Model;

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

	virtual void SetPosition(D3DXVECTOR3 Position)
	{
		m_Position = Position;
	}

	void SetRotation(D3DXVECTOR3 Rotation)
	{
		m_Rotation = Rotation;
	}
	D3DXVECTOR3 GetPosition() { return m_Position; }
	D3DXVECTOR3 GetRotation() { return m_Rotation; }
	
	const D3DXVECTOR3& GetPositionReference()const 
	{
		return m_Position;
	}

	D3DXVECTOR3 GetForward()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot,
			m_Rotation.y, m_Rotation.x, m_Rotation.z);

		D3DXVECTOR3 forward;
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;

		return forward;
	}

	D3DXVECTOR3 GetRight()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot,
			m_Rotation.y, m_Rotation.x, m_Rotation.z);

		D3DXVECTOR3 forward;
		forward.x = rot._11;
		forward.y = rot._12;
		forward.z = rot._13;

		return forward;
	}

	D3DXVECTOR3 GetLeft() {
		return GetRight() * -1.0f;
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

	//void SetModel(std::shared_ptr<Model> pModel) { m_Model = pModel; }
	//std::string GetFileName() { return m_FileName; }
};

