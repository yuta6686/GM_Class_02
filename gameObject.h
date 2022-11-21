#pragma once

#include "main.h"
#include "texture.h"
#include "vertexShader.h"
#include "pixelShader.h"
#include "my_math.h"
#include "component.h"

enum COMPONENT_LAYER {
	COMLAYER_FIRST = 0,
	COMLAYER_SECOND,
	COMLAYER_CHANGEVERTEX,
	COMLAYER_SHADER,
	COMLAYER_MATRIX,	
	COMLAYER_DRAW,
	COMLAYER_NUM_MAX,
};


class Model;

class GameObject
{
protected:
	bool m_Destroy = false;
	bool m_NoUpdate = false;

	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_Rotation;
	D3DXVECTOR3 m_Scale;
	
	std::list<Component*> m_ComponentList[COMLAYER_NUM_MAX];

	std::string m_TypeName = "none";
public:
	virtual void Init()	 = 0;
	virtual void Uninit()= 0;
	virtual void Update()= 0;
	virtual void Draw()	 = 0;
	virtual void DrawImgui() {}

	virtual void LastInit() {}

	
	virtual void SetPosition(D3DXVECTOR3 Position)
	{
		m_Position = Position;
	}

	void AddPosition(D3DXVECTOR3 apos)
	{
		m_Position += apos;
	}

	void AddPosition(float apos) {
		m_Position.x += apos;
		m_Position.y += apos;
		m_Position.z += apos;
	}

	void SetRotation(D3DXVECTOR3 Rotation)
	{
		m_Rotation = Rotation;
	}
	virtual void SetScale(D3DXVECTOR3 Scale)
	{
		m_Scale = Scale;
	}

	D3DXVECTOR3 GetPosition()const { return m_Position; }
	D3DXVECTOR3 GetRotation()const { return m_Rotation; }
	D3DXVECTOR3 GetScale()const { return m_Scale; }

	D3DXVECTOR3* GetPositionPointer() { return &m_Position; }
	virtual float GetLength() { return D3DXVec3Length(&m_Scale); }
	
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

	D3DXVECTOR3 GetUp()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot,
			m_Rotation.y, m_Rotation.x, m_Rotation.z);

		D3DXVECTOR3 up;
		up.x = rot._21;
		up.y = rot._22;
		up.z = rot._23;

		return up;
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

	void SetNoUpdate(const bool& flag = true) { m_NoUpdate = flag; }

	//void SetModel(std::shared_ptr<Model> pModel) { m_Model = pModel; }
	//std::string GetFileName() { return m_FileName; }

	template<class T>
	T* GetComponent()
	{
		for (int i = 0; i < COMLAYER_NUM_MAX; i++) {
			for (auto com : m_ComponentList[i]) {
				T* buff = dynamic_cast<T*>(com);
				if (buff != nullptr)
					return buff;
			}
		}

		return nullptr;
	}

	template<class T>
	std::vector<T*> GetComponents()
	{
		std::vector<T*> result;

		for (int i = 0; i < COMLAYER_NUM_MAX; i++) {
			for (auto com : m_ComponentList[i]) {		
				T* buff = dynamic_cast<T*>(com);
				if (buff != nullptr) {
					result.push_back(buff);
				}					
			}
		}

		return result;
	}

	template<class T>
	T* AddComponent(int Layer)
	{
		T* buff = new T();
		buff->m_Parent = this;
		m_ComponentList[Layer].push_back(buff);
		buff->Init();
		return buff;
	}

	Component* AddComponent(Component* pComponent, int layer) {
		pComponent->Init();
		m_ComponentList[layer].push_back(pComponent);
		return pComponent;
	}

	std::string GetTypeName()const { return m_TypeName; }
};

