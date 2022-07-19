#pragma once


#include <memory>

class GameObject;

class Component
{
public:
	GameObject* m_Parent;

	std::unique_ptr<GameObject> m_upParent;


	virtual void Init() = 0;
	virtual void Uninit()=0;
	virtual void Update()=0;
	virtual void Draw()=0;
};