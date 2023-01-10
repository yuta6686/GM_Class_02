#pragma once
/** ---------------------------------------------------------
 *  [co_state_machine.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2023/1/10
 * ------------------------summary--------------------------
 * @brief	ステートマシンをステートパターンで作る
 *			汎用的なステートマシンを作れた。
 * @link	https://yuta6686.atlassian.net/browse/AS-11
 ** ---------------------------------------------------------*/
#include "component_object.h"

class Context;


// ↓これを継承して別のステートマシンを作成する
class StateMachine :
    public ComponentObject
{
protected:
	Context* _context;
public:
	// InitInternalよりも先にこれが呼ばれるので、継承先のInitはこれが呼ばれることになる？といいな
	virtual void Init()override;

	// CO_StateMachineで使いたいInit 継承先で使うときはこれを上書きする
	virtual void InitInternal()override;
};


class State : public Component
{
protected:
	Context* _context;
	std::string _name;

public:
	State(std::string name) :_name(name) {}
	virtual ~State(){}
	void SetContext(Context* context)
	{
		this->_context = context;
	}
	
	// Component を介して継承されました
	virtual void Init() override {};
	virtual void Uninit() override {};
	virtual void Update() override=0;
	virtual void Draw() override {};
	virtual void DrawImgui() override {};


	std::string GetName() { return _name; }
};

class Context :public Component
{
private:
	State* _state;
public:

	Context(State* state);

	void TransitionTo(State* state);	

	// Component を介して継承されました
	virtual void Init() override;

	virtual void Uninit() override;

	virtual void Update() override;

	virtual void Draw() override;

	virtual void DrawImgui() override;

};


class StateEmpty : public State
{
	inline static const std::string NAME = "Empty";
public:
	StateEmpty() :State(NAME) {}
	virtual void Update() override {};
};
class StateA : public State
{
	inline static const std::string NAME = "A";
public:
	StateA() :State(NAME) {}	
	virtual void Update() override;
};
class StateB : public State
{
	inline static const std::string NAME = "B";
public:
	StateB() :State(NAME) {}
	virtual void Update() override;
};
