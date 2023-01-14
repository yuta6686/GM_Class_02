#include "stdafx.h"
#include "state_machine.h"

// InitInternalよりも先にこれが呼ばれるので、継承先のInitはこれが呼ばれることになる？といいな
void CO_StateMachine::Init()
{
	_context = new Context(new StateEmpty());
	AddComponent(_context, COMLAYER_SECOND);	

	ComponentObject::Init();
}

// CO_StateMachineで使いたいInit 継承先で使うときはこれを上書きする
void CO_StateMachine::InitInternal()
{
	AddComponent<ImGuiComponent>(COMLAYER_DRAW)->SetIsUse(true);
	
	_context->TransitionTo(new StateA());	
}

void StateMachine::Init()
{
	_context = new Context(new StateEmpty());

	// コンポーネントとして作ってはいるけど、コンポーネントとして使ってないので、(AddComponentしてない)
	// m_Parentは手動でつけなきゃいけない。
	_context->m_Parent = m_Parent;

	InitInternal();

	_context->Init();
}

void StateMachine::Uninit()
{
	_context->Uninit();
}

void StateMachine::Update()
{
	_context->Update();
}

void StateMachine::Draw()
{
	_context->Draw();
}

void StateMachine::DrawImgui()
{
	_context->DrawImgui();
}


Context::Context(State* state)
	: _state(nullptr)
{
	TransitionTo(state);
}

void Context::TransitionTo(State* state)
{
	if (_state != nullptr)
		delete _state;

	_state = state;
	_state->SetContext(this);

	_state->Init();
}

void Context::Init()
{	
	_state->Init();
}

void Context::Uninit()
{
	_state->Uninit();
}

void Context::Update()
{
	_state->Update();
}

void Context::Draw()
{
	_state->Draw();
}

void Context::DrawImgui()
{
	_state->DrawImgui();

	if (!MyImgui::_myFlag["StateMachine"])return;

	ImGui::Text("%s", _state->GetName().c_str());
}


void StateA::Update()
{
	if (GetKeyboardTrigger(DIK_O))
		_context->TransitionTo(new StateB());
}


void StateB::Update()
{
	if (GetKeyboardTrigger(DIK_O))
		_context->TransitionTo(new StateA());
}

