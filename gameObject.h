#pragma once
class GameObject
{
protected:
	bool m_Destroy = false;

	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_Rotateion;
	D3DXVECTOR3 m_Scale;
public:
	GameObject() = default;
	virtual ~GameObject() = default;

	virtual void Init()	 = 0;
	virtual void Uninit()= 0;
	virtual void Update()= 0;
	virtual void Draw()	 = 0;

	void SetPosition(D3DXVECTOR3 Position)
	{
		m_Position = Position;
	}

	void SetDestroy() {
		m_Destroy = true;
	}

	bool Destroy() {
		if (m_Destroy) {
			Uninit();
			delete this;
			return true;
		}
		else {
			return false;
		}
	}
};

