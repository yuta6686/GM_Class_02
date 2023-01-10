#pragma once
/** ---------------------------------------------------------
 *  [co_state_machine.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2023/1/10
 * ------------------------summary--------------------------
 * @brief	�X�e�[�g�}�V�����X�e�[�g�p�^�[���ō��
 *			�ėp�I�ȃX�e�[�g�}�V������ꂽ�B
 * @link	https://yuta6686.atlassian.net/browse/AS-11
 ** ---------------------------------------------------------*/
#include "component_object.h"

class Context;


// ��������p�����ĕʂ̃X�e�[�g�}�V�����쐬����
class StateMachine :
    public ComponentObject
{
protected:
	Context* _context;
public:
	// InitInternal������ɂ��ꂪ�Ă΂��̂ŁA�p�����Init�͂��ꂪ�Ă΂�邱�ƂɂȂ�H�Ƃ�����
	virtual void Init()override;

	// CO_StateMachine�Ŏg������Init �p����Ŏg���Ƃ��͂�����㏑������
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
	
	// Component ����Čp������܂���
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

	// Component ����Čp������܂���
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
