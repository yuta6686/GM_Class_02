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

	virtual void DrawImgui()override
	{
		for (int i = 0; i < COMLAYER_NUM_MAX; i++) {
			for (auto com : m_ComponentList[i]) {
				com->DrawImgui();
			}
		}
	}
};

