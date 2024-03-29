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

	AddComponent<ImGuiComponent>(COMLAYER_FIRST)->SetIsUse(true);

	// StateMachineを継承したEnemy専用のEnemyStateMachineを作って、ここでAddする
	AddComponent<EnemyStateMachine_Component>(COMLAYER_SECOND);

	ComponentObject::Init();

	m_Scale = { 2.0f,2.0f,2.0f };
}

void EnemyStateMachine_Component::InitInternal()
{
	// 初期状態は待機にする
	_context->TransitionTo(new EnemyStateIdle());			
}


// Stateとしてエネミーの待機状態の実装
// https://yuta6686.atlassian.net/browse/AS-16
// -------------------------------------------
void EnemyStateIdle::Update()
{
	// エネミーの突進処理の後の待機状態
	if (_time >= IDLE_TIME)
	{
		_time = 0;
		_context->TransitionTo(new EnemyStateApproach());
		return;
	}

	_time++;
}

void EnemyStateMachine_Component::DrawImgui()
{
	_context->DrawImgui();

	if (!MyImgui::_myFlag["EnemyStateMachine_Component"])return;

	ImGui::Text("%s", _context->GetState()->GetName().c_str());

}

void EnemyStateApproach::Init()
{
	// このステート時は接近するComponentをアタッチする
	_context->m_Parent->AddComponent<TrackingComponent>(COMLAYER_SECOND)->SetSpeed(APPROACH_SPEED);

	// プレイヤーとの距離を計算するために取得
	_player = Manager::GetScene()->GetGameObject<Player>();
}

// Stateとしてエネミーの接近状態の実装
// https://yuta6686.atlassian.net/browse/AS-17 
// -------------------------------------------
void EnemyStateApproach::Update()
{
	if (_player == nullptr)return;

	// プレイヤーに近づく

	// プレイヤーとエネミーの距離を計算する
	const D3DXVECTOR3 playerPos = _player->GetPosition();
	const D3DXVECTOR3 enemyPos = _context->m_Parent->GetPosition();
	D3DXVECTOR3 vec = playerPos - enemyPos;

	// 距離
	const float lengthSq = D3DXVec3Length(&vec);

	// エネミーからプレイヤーへのベクトル正規化
	D3DXVec3Normalize(&vec, &vec);
	
	if (lengthSq < APPROACH_DISTANCE)
	{
		// EnemyStateApproach::Uninitの_context->m_Parent->GetComponent<TrackingComponent>()で終了時エラーが出る
		// https://yuta6686.atlassian.net/browse/AS-19
		auto tracking = _context->m_Parent->GetComponent<TrackingComponent>();
		
		// 次のステートでは不要なので、Remove
		if (tracking)
			tracking->SetRemove();

		// 突進ステートへ
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


// Stateとしてエネミーの攻撃の実装
// https://yuta6686.atlassian.net/browse/AS-14
// -------------------------------------------
void EnemyStateRush::Update()
{
	// エネミーに突進する
	_context->m_Parent->GetComponent<VelocityComponent>()->m_Velocity += _vec * RUSH_SPEED;

	_context->TransitionTo(new EnemyStateIdle());
}

