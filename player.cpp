#include "main.h"
#include "renderer.h"
#include "model.h"
#include "player.h"
#include "Bullet.h"
#include "manager.h"
#include "scene.h"
#include "Item.h"
#include "audio.h"
#include "Shadow.h"
#include "ShootBullet_Idle.h"
#include "Cylinder.h"

using namespace std;

#define PLAYER_SPEED 0.01f

static char texName[] = { "asset\\model\\torii.obj" };
static float scale = 0.5f;

static std::shared_ptr<Scene> g_Scene;


void Player::Init()
{
	std::shared_ptr<Scene> scene = Manager::GetScene();
	m_ShotSE = scene->AddGameObject<Audio>(LAYER_AUDIO);
	m_ShotSE->Load("asset\\audio\\ビーム音.wav");



	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(scale, scale, scale);

	g_Scene = Manager::GetScene();

	m_Shadow = g_Scene->AddGameObject<Shadow>(LAYER_3D);

	m_ShootBullet = new ShootBullet_Idle();
	m_ShootBullet->Init();

	m_Velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_TypeName = "Player";
	

//	↓ここにコンポーネントついか　--------------------------------------	

	AddComponent<ShaderComponent>(COMLAYER_SHADER);

	AddComponent<MatrixComponent>(COMLAYER_MATRIX)->SetIsInvertXYRotate();

	auto* mdc = AddComponent<ModelDrawComponent>(COMLAYER_DRAW);
	mdc->SetSourcePath("asset\\model\\torii.obj");
	//mdc->SetIsVariable(true);

	AddComponent<PlayerRotateComponent>(COMLAYER_SECOND);

	AddComponent< ImGuiComponent>(COMLAYER_SECOND);

//	↑ここにコンポーネントついか　--------------------------------------
	ComponentObject::Init();
}

void Player::Uninit()
{
	m_ShootBullet->Uninit();
	delete m_ShootBullet;

	ComponentObject::Uninit();
}

void Player::Update()
{

	if (m_IsNoMove) {
		GetComponent<PlayerRotateComponent>()->Update();
		return;
	}
	else
	{
		ComponentObject::Update();
	}

	//	プレイヤー移動処理
	PlayerMove();

	//	バレット撃つ処理
	ShootBulletFunc();

	//	アイテム取得	
	GetItem();

	D3DXVECTOR3 shadowPos = m_Position;
	shadowPos.y = 0.25f;
	m_Shadow->SetPosition(shadowPos);
	m_Shadow->SetScale(m_Scale * 2.0f);



	
}

void Player::DrawImgui()
{
#ifdef _DEBUG


	m_ShootBullet->Draw();

	ImGui::Separator();

	ImGui::Checkbox("IsUseBullet", &m_IsUseBullet);


	if (ImGui::Button("Player->Jump")) {
		if (m_Position.y >= 0.2f) {
			m_Velocity.y = JUMP * 1.5f;
		}
		else {
			m_Velocity.y = JUMP;
		}
	}	

	ImGui::Separator();

	ComponentObject::DrawImgui();

#endif // _DEBUG
}

void Player::PlayerMove()
{
	D3DXVECTOR3 forward = GetForward();



	//	プレイヤー移動処理
	if (GetKeyboardPress(DIK_W)) {

		m_Velocity.z += PLAYER_SPEED * forward.z;
		m_Velocity.x += PLAYER_SPEED * forward.x;		
	}
	if (GetKeyboardPress(DIK_S)) {
		m_Velocity.z -= PLAYER_SPEED * forward.z;
		m_Velocity.x -= PLAYER_SPEED * forward.x;
	}
	if (GetKeyboardPress(DIK_A)) {
		m_Velocity.z += PLAYER_SPEED * GetLeft().z;
		m_Velocity.x += PLAYER_SPEED * GetLeft().x;
	}
	if (GetKeyboardPress(DIK_D)) {
		m_Velocity.z += PLAYER_SPEED * GetRight().z;
		m_Velocity.x += PLAYER_SPEED * GetRight().x;
	}


	//if (m_PlayerRotation.y > D3DX_PI) {
	//	m_PlayerRotation.y -= D3DX_PI * 2.0f;
	//}
	//else if (m_PlayerRotation.y < -D3DX_PI) {
	//	m_PlayerRotation.y += D3DX_PI * 2.0f;
	//}

	//	ジャンプ
	if (GetKeyboardTrigger(DIK_SPACE)) {
		if (m_Position.y >= 0.2f) {
			m_Velocity.y = JUMP * 1.5f;
		}
		else {
			m_Velocity.y = JUMP;
		}
	}

	//	重力
	m_Velocity.y -= GRAVITY;

	//	減衰
	m_Velocity.x *= ATTENUATION.x;
	m_Velocity.y *= ATTENUATION.y;
	m_Velocity.z *= ATTENUATION.z;



	D3DXVECTOR3 oldPos = m_Position;

	m_Position += m_Velocity;

	//	接台

	float groundHeight = 0.0f;
	std::vector<Cylinder*> clylist = g_Scene->GetGameObjects<Cylinder>();
	for (auto cly : clylist) {
		D3DXVECTOR3 clyPos = cly->GetPosition();
		D3DXVECTOR3 clyScale = cly->GetScale();

		D3DXVECTOR3 direction = m_Position - clyPos;
		direction.y = 0.0f;

		float length = D3DXVec3Length(&direction);

		if (length < clyScale.x) {
			if (m_Position.y < clyPos.y + clyScale.y - 0.5f) {
				m_Position.x = oldPos.x;
				m_Position.z = oldPos.z;
			}
			else {
				groundHeight = clyPos.y + clyScale.y;
			}

			break;
		}
	}

	//	接地	
	if (m_Position.y < groundHeight &&
		m_Velocity.y < 0.0f) {
		m_Position.y = groundHeight;
		//	m_Velocity.y = 0;

		//	反発
		{
			m_Velocity.y = m_Velocity.y * -0.25f;

			if (m_Velocity.y < 0.2f) {
				m_Velocity.y = 0;
			}
		}
	}
}


void Player::GetItem()
{
	//	アイテム取得
	std::vector<item*> itemList
		= g_Scene->GetGameObjects<item>();

	for (auto item : itemList) {
		D3DXVECTOR3 enemyPosition = item->GetPosition();
		D3DXVECTOR3 direction = m_Position - enemyPosition;
		float length = D3DXVec3Length(&direction);

		if (length < 2.0f) {
			item->SetDestroy();
			return;
		}
	}
}

void Player::ShootBulletFunc()
{
	if (m_IsUseBullet == false)return;

	m_ShootBullet->Update();	

	if (m_ShootBullet->GetIsNextState()) {
		//	次のstateのポインタだけもらう。
		ShootBullet* sb = m_ShootBullet->CreateNextState();

		//	今のポインタは消す。
		m_ShootBullet->Uninit();
		delete m_ShootBullet;

		//	新しいポインタを作る
		m_ShootBullet = sb;
		m_ShootBullet->Init();
	}
}
