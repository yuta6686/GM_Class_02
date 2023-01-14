#pragma once
/** ---------------------------------------------------------
 *  Component [component.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2022/11/21
 * ------------------------summary--------------------------
 * @brief  
 * 
 ** ---------------------------------------------------------*/

class GameObject;

class Component
{
	bool _removeComponent = false;
protected:
	bool _isValidity = true;
public:
	GameObject* m_Parent;
	
	virtual void Init() = 0;
	virtual void Uninit()=0;
	virtual void Update()=0;
	virtual void Draw()=0;
	virtual void DrawImgui()=0;

	void SetRemove()
	{
		_removeComponent = true;
	}
	bool Remove()
	{
		if (_removeComponent)
		{
			Uninit();
			delete this;
			return true;
		}
		return false;
	}
};