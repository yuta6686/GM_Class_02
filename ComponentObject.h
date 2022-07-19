#pragma once
#include "gameObject.h"

//	デフォルトインクルード
#include "ShaderComponent.h"
#include "MatrixComponent.h"
#include "ModelDrawComponent.h"
#include "TransformInit.h"

class ComponentObject :
    public GameObject
{
public:
	virtual void Init() 
	{
		for (int i = 0; i < COMLAYER_NUM_MAX; i++) {
			for (auto com : m_ComponentList[i]) {
				com->Init();
			}
		}
	}
	virtual void Uninit()
	{
		for (int i = 0; i < COMLAYER_NUM_MAX; i++) {
			for (auto com : m_ComponentList[i]) {
				com->Uninit();
			}
		}
	}
	virtual void Update() 
	{
		for (int i = 0; i < COMLAYER_NUM_MAX; i++) {
			for (auto com : m_ComponentList[i]) {
				com->Update();
			}
		}
	}
	virtual void Draw() 
	{
		for (int i = 0; i < COMLAYER_NUM_MAX; i++) {
			for (auto com : m_ComponentList[i]) {
				com->Draw();
			}
		}
	}
};

