#pragma once


#include <memory>

class GameObject;

class Component
{
public:
	GameObject* m_Parent;
	


	virtual void Init() = 0;
	virtual void Uninit()=0;
	virtual void Update()=0;
	virtual void Draw()=0;
	virtual void DrawImgui()=0;
};