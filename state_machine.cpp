#include "stdafx.h"
#include "state_machine.h"

// InitInternal������ɂ��ꂪ�Ă΂��̂ŁA�p�����Init�͂��ꂪ�Ă΂�邱�ƂɂȂ�H�Ƃ�����
void CO_StateMachine::Init()
{
	_context = new Context(new StateEmpty());
	AddComponent(_context, COMLAYER_SECOND);	

	ComponentObject::Init();
}

// CO_StateMachine�Ŏg������Init �p����Ŏg���Ƃ��͂�����㏑������
void CO_StateMachine::InitInternal()
{
	AddComponent<ImGuiComponent>(COMLAYER_DRAW)->SetIsUse(true);
	
	_context->TransitionTo(new StateA());	
}

void StateMachine::Init()
{
	_context = new Context(new StateEmpty());

	// �R���|�[�l���g�Ƃ��č���Ă͂��邯�ǁA�R���|�[�l���g�Ƃ��Ďg���ĂȂ��̂ŁA(AddComponent���ĂȂ�)
	// m_Parent�͎蓮�ł��Ȃ��Ⴂ���Ȃ��B
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

