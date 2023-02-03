#pragma once
/** ---------------------------------------------------------
 *  [co_title_ui.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2023/2/2
 * ------------------------summary--------------------------
 * @brief  
 * @link https://yuta6686.atlassian.net/browse/AS-51
 ** ---------------------------------------------------------*/
#include "component_object.h"
#include "state_machine.h"


class CO_TitleUI :
    public ComponentObject
{
	class UserInterfaceComponent* _uiComponent;
public:
	virtual void InitInternal() ;
	virtual void UninitInternal();
	virtual void UpdateInternal();
	virtual void DrawInternal();
	virtual void DrawImguiInternal();
};

// https://yuta6686.atlassian.net/browse/AS-52 ステートマシンで画像切替処理を作成する
class TitleUI_StateMachine :
	public StateMachine
{
public:
	virtual void InitInternal() override;
};

class TitleUIState_RightMouseDrag :
	public State
{
	inline static const std::string NAME = "Right Mouse Drag";
	inline static const std::string TEXTURE = "asset\\texture\\RightMouseDrag.png";
public:
	TitleUIState_RightMouseDrag() :State(NAME) {}
	
	virtual void Init()override;
	virtual void Update() override;
};

class TitleUIState_Idle :
	public State
{
	inline static const std::string NAME = "Idle";
	inline static const std::string TEXTURE = "asset\\texture\\RightMouseDrag.png";
	int _idleFrame = 0;
	int _idleMaxFrame = 60;	
public:
	TitleUIState_Idle(const int& idleMaxFrame) :State(NAME),
		_idleFrame(0),
		_idleMaxFrame(idleMaxFrame) {}

	virtual void Init()override;
	virtual void Update() override;
};

class TitleUIState_Space :
	public State
{
	inline static const std::string NAME = "Space";
	inline static const std::string TEXTURE = "asset\\texture\\space_key.png";

	inline static const int NO_OPERATION_FRAME_MAX = 180;
	int _noOperationFrame = 0;
public:
	TitleUIState_Space() :State(NAME) {}

	virtual void Init()override;
	virtual void Update() override;
};