#pragma once
/** ---------------------------------------------------------
 *  ComponentObject [component_object.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2022/11/21
 * ------------------------summary--------------------------
 * @brief  コンポーネントをくっつけるオブジェクト
 ** ---------------------------------------------------------*/
// 
// ? コンポーネントじゃなくて、ツリー構造にしたほうがいいのでは。
///
#include "gameObject.h"

//	デフォルトインクルード
#include "shader_component.h"
#include "matrix_component.h"
#include "model_draw_component.h"
#include "transform_init.h"
#include "imgui_component.h"
#include "count_component.h"


class ComponentObject :
	public GameObject
{
	
public:
	virtual void Init()
	{
		InitInternal();

		for (int i = 0; i < COMLAYER_NUM_MAX; i++) {
			for (auto com : m_ComponentList[i]) {
				com->Init();
			}
		}
	}
	virtual void Uninit()
	{
		UninitInternal();

		for (int i = 0; i < COMLAYER_NUM_MAX; i++) {
			for (auto com : m_ComponentList[i]) {
				com->Uninit();
				delete com;
				com = nullptr;
			}
			m_ComponentList[i].clear();
		}
	}
	virtual void Update()
	{
		UpdateInternal();

		for (int i = 0; i < COMLAYER_NUM_MAX; i++) {
			for (auto com : m_ComponentList[i]) {
				com->Update();
			}

			m_ComponentList[i].remove_if([](Component* component) {return component->Remove(); });
		}

	}
	virtual void Draw()
	{
		DrawInternal();

		for (int i = 0; i < COMLAYER_NUM_MAX; i++) {
			for (auto com : m_ComponentList[i]) {
				com->Draw();
			}
		}
	}

	virtual void DrawImgui()override
	{
		DrawImguiInternal();

		for (int i = 0; i < COMLAYER_NUM_MAX; i++) {
			for (auto com : m_ComponentList[i]) {
				com->DrawImgui();
			}
		}
	}
	

protected:
	virtual void InitInternal() {};
	virtual void UninitInternal() {};
	virtual void UpdateInternal() {};
	virtual void DrawInternal() {};
	virtual void DrawImguiInternal() {};
};

