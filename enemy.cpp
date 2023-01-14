#include "Enemy.h"
#include "random_velocity_component.h"
#include "random_jump_component.h"
#include "tracking_component.h"
#include "gravity_component.h"
#include "player.h"


void Enemy::Init()
{

	Enemy_Interface::Init();

	ModelDrawComponent* mdc = AddComponent< ModelDrawComponent>(COMLAYER_DRAW);
	mdc->SetSourcePath("asset\\model\\stone_white.obj");
	mdc->SetIsVariable(true);




	ComponentObject::Init();
}

void Enemy_Tracking::Init()
{

	Enemy_Interface::Init();
	ModelDrawComponent* mdc = AddComponent< ModelDrawComponent>(COMLAYER_DRAW);
	mdc->SetSourcePath("asset\\model\\stone_white.obj");
	mdc->SetIsVariable(true);

	AddComponent<TrackingComponent>(COMLAYER_SECOND);


	ComponentObject::Init();
}

void Enemy_Tracking_Fast::InitInternal()
{

	Enemy_Interface::Init();

	ModelDrawComponent* mdc = AddComponent< ModelDrawComponent>(COMLAYER_DRAW);
	mdc->SetSourcePath("asset\\model\\stone_white.obj");
	mdc->SetIsVariable(true);

	AddComponent<TrackingComponent>(COMLAYER_SECOND)->SetSpeed(0.3f);

}

void Enemy_Tracking_Late::Init()
{

	Enemy_Interface::Init();

	ModelDrawComponent* mdc = AddComponent< ModelDrawComponent>(COMLAYER_DRAW);
	mdc->SetSourcePath("asset\\model\\stone_white.obj");

	mdc->SetIsVariable(true);

	AddComponent<TrackingComponent>(COMLAYER_SECOND)->SetSpeed(0.01f);



	ComponentObject::Init();
}

void Enemy_Move_Straight::Init()
{

	Enemy_Interface::Init();

	ModelDrawComponent* mdc = AddComponent< ModelDrawComponent>(COMLAYER_DRAW);
	mdc->SetSourcePath("asset\\model\\stone_white.obj");
	mdc->SetIsVariable(true);



	AddComponent<RandomVelocityComponent>(COMLAYER_SECOND)->SetSpeed(0.1f);


	ComponentObject::Init();
}

void Enemy_Jump::Init()
{

	Enemy_Interface::Init();

	ModelDrawComponent* mdc = AddComponent< ModelDrawComponent>(COMLAYER_DRAW);
	mdc->SetSourcePath("asset\\model\\stone_white.obj");
	mdc->SetIsVariable(true);

	AddComponent< GravityComponent>(COMLAYER_SECOND);

	AddComponent<RandomVelocityComponent>(COMLAYER_SECOND)->SetSpeed(0.1f);

	AddComponent< RandomJumpComponent>(COMLAYER_DRAW);

	ComponentObject::Init();
}

void Enemy_Boss::Init()
{

	Enemy_Interface::Init();

	ModelDrawComponent* mdc = AddComponent< ModelDrawComponent>(COMLAYER_DRAW);
	mdc->SetSourcePath("asset\\model\\enemy_boss.obj");
	mdc->SetIsVariable(true);


	AddComponent< GravityComponent>(COMLAYER_SECOND);

	AddComponent<RandomVelocityComponent>(COMLAYER_SECOND)->SetSpeed(0.5f);

	AddComponent< RandomJumpComponent>(COMLAYER_DRAW);

	ComponentObject::Init();

	m_Scale = { 2.0f,2.0f,2.0f };
}

void Enemy_Rush::Init()
{
	Enemy_Interface::Init();

	ModelDrawComponent* mdc = AddComponent< ModelDrawComponent>(COMLAYER_DRAW);
	mdc->SetSourcePath("asset\\model\\enemy_boss.obj");
	mdc->SetIsVariable(true);


	AddComponent< GravityComponent>(COMLAYER_SECOND);

	//AddComponent<RandomVelocityComponent>(COMLAYER_SECOND)->SetSpeed(0.5f);

	//AddComponent< RandomJumpComponent>(COMLAYER_DRAW);

	AddComponent<ImGuiComponent>(COMLAYER_FIRST)->SetIsUse(true);

	// StateMachine���p������Enemy��p��EnemyStateMachine������āA������Add����
	AddComponent<EnemyStateMachine_Component>(COMLAYER_SECOND);

	ComponentObject::Init();

	m_Scale = { 2.0f,2.0f,2.0f };
}

void EnemyStateMachine_Component::InitInternal()
{
	// ������Ԃ͑ҋ@�ɂ���
	_context->TransitionTo(new EnemyStateIdle());		
}

void EnemyStateMachine_Component::DrawImgui()
{
	_context->DrawImgui();

	if (!MyImgui::_myFlag["EnemyStateMachine_Component"])return;

	ImGui::Text("%s", _context->GetState()->GetName().c_str());

}

// State�Ƃ��ăG�l�~�[�̑ҋ@��Ԃ̎���
// https://yuta6686.atlassian.net/browse/AS-16
// -------------------------------------------
void EnemyStateIdle::Update()
{
	// �G�l�~�[�̓ːi�����̌�̑ҋ@���
	if (_time >= IDLE_TIME)
	{
		_time = 0;
		_context->TransitionTo(new EnemyStateApproach());
		return;
	}

	_time++;
}



void EnemyStateApproach::Init()
{
	_context->m_Parent->AddComponent<TrackingComponent>(COMLAYER_SECOND)->SetSpeed(0.3f);
	_player = Manager::GetScene()->GetGameObject<Player>();
}

// State�Ƃ��ăG�l�~�[�̐ڋߏ�Ԃ̎���
// https://yuta6686.atlassian.net/browse/AS-17 
// -------------------------------------------
void EnemyStateApproach::Update()
{
	if (_player == nullptr)return;

	// �v���C���[�ɋ߂Â�

	// �v���C���[�ƃG�l�~�[�̋������v�Z����
	const D3DXVECTOR3 playerPos = _player->GetPosition();
	const D3DXVECTOR3 enemyPos = _context->m_Parent->GetPosition();
	D3DXVECTOR3 vec = playerPos - enemyPos;
	const float lengthSq = D3DXVec3Length(&vec);
	D3DXVec3Normalize(&vec, &vec);

	if (lengthSq < APPROACH_DISTANCE)
	{
		// EnemyStateApproach::Uninit��_context->m_Parent->GetComponent<TrackingComponent>()�ŏI�����G���[���o��
		// https://yuta6686.atlassian.net/browse/AS-19
		auto tracking = _context->m_Parent->GetComponent<TrackingComponent>();

		if (tracking)
			tracking->SetRemove();

		_context->TransitionTo(new EnemyStateRush(vec));
	}
}

void EnemyStateApproach::DrawImgui()
{
	if (_player == nullptr)return;
	if (_context == nullptr)return;
	const D3DXVECTOR3 playerPos = _player->GetPosition();
	const D3DXVECTOR3 enemyPos = _context->m_Parent->GetPosition();
	const D3DXVECTOR3 direction = playerPos - enemyPos;
	const float length = D3DXVec3Length(&direction);
	ImGui::Text("length: [%.2f]", length);
	
}


// State�Ƃ��ăG�l�~�[�̍U���̎���
// https://yuta6686.atlassian.net/browse/AS-14
// -------------------------------------------
void EnemyStateRush::Update()
{
	// �G�l�~�[�ɓːi����
	_context->m_Parent->GetComponent<VelocityComponent>()->m_Velocity += _vec * 0.5f;

	_context->TransitionTo(new EnemyStateIdle());
}

