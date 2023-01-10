#include "stdafx.h"
#include "state_machine.h"

// InitInternal������ɂ��ꂪ�Ă΂��̂ŁA�p�����Init�͂��ꂪ�Ă΂�邱�ƂɂȂ�H�Ƃ�����
void StateMachine::Init()
{
	_context = new Context(new StateEmpty());
	AddComponent(_context, COMLAYER_SECOND);	

	ComponentObject::Init();
}

// CO_StateMachine�Ŏg������Init �p����Ŏg���Ƃ��͂�����㏑������
void StateMachine::InitInternal()
{
	AddComponent<ImGuiComponent>(COMLAYER_DRAW)->SetIsUse(true);
	
	_context->TransitionTo(new StateA());	
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
	if (!MyImgui::_myFlag["StateMachine"])return;
	_state->DrawImgui();

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
