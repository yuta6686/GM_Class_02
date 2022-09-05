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

#include "StageLimitComponent.h"
#include "HPComponent.h"
#include "CollisionComponent_Player.h"

using namespace std;

#define PLAYER_SPEED 0.01f

static char texName[] = { "asset\\model\\torii.obj" };
static float scale = 1.0f;

static std::shared_ptr<Scene> g_Scene;


void Player::Init()
{
	std::shared_ptr<Scene> scene = Manager::GetScene();
	m_ShotSE = scene->AddGameObject<Audio>(LAYER_AUDIO);
	m_ShotSE->Load("asset\\audio\\SE_Shoot1.wav");

	m_SEJump = scene->AddGameObject<Audio>(LAYER_AUDIO);
	m_SEJump->Load("asset\\audio\\SE_Jump.wav");

	m_SELanding = scene->AddGameObject<Audio>(LAYER_AUDIO);
	m_SELanding->Load("asset\\audio\\SE_Landing.wav");
	

	m_Position = D3DXVECTOR3(0.0f, 2.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(scale, scale, scale);

	g_Scene = Manager::GetScene();

	

	//m_ShootBullet = new ShootBullet_Idle();
	//m_ShootBullet->Init();	

	m_TypeName = "Player";

	m_Particle = g_Scene->AddGameObject<ParticleObject>(LAYER_3D);
	

//	↓ここにコンポーネントついか　--------------------------------------	

	AddComponent<ShaderComponent>(COMLAYER_SHADER);

	AddComponent<MatrixComponent>(COMLAYER_MATRIX)->SetIsInvertXYRotate();

	auto* mdc = AddComponent<ModelDrawComponent>(COMLAYER_DRAW);
	mdc->SetSourcePath("asset\\model\\bow.obj");
	mdc->SetIsVariable(true);

	AddComponent<PlayerRotateComponent>(COMLAYER_SECOND);

	AddComponent< ShootBulletComponent>(COMLAYER_SECOND);

	


	m_VelocityCom = AddComponent<VelocityComponent>(COMLAYER_SECOND);

	AddComponent< StageLimitComponent>(COMLAYER_SECOND);

	AddComponent< HPComponent>(COMLAYER_SECOND);

	AddComponent< CollisionComponent_Player>(COMLAYER_SECOND);
	

//	↑ここにコンポーネントついか　--------------------------------------

	AddComponent<MonochromeComponent>(COMLAYER_SECOND);

	AddComponent< ImGuiComponent>(COMLAYER_SECOND);

	ComponentObject::Init();

	
	
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

	//	アイテム取得	
	GetItem();




	
}

void Player::Draw()
{
	if (GetComponent<HPComponent>()->GetIsDeath())return;
	ComponentObject::Draw();
}

void Player::DrawImgui()
{
#ifdef _DEBUG

	

	ImGui::Separator();

	ImGui::Text("Velocity Length:%.2f",D3DXVec3Length(&m_VelocityCom->m_Velocity));
	ImGui::Text("Velocity Y:%.2f", m_VelocityCom->m_Velocity.y);


	ImGui::Checkbox("IsPlayer_Move", &m_IsUseBullet);

	static ImVec4 color = { 1.0f,1.0f,1.0f,1.0f };

	ImGui::ColorEdit4("color", (float*)&color);

	MyMath::FromImVec4ToD3DXCOLOR(&m_Color ,color);
	GetComponent< ModelDrawComponent>()->SetDiffuse(m_Color);

	ImGui::Separator();

	ComponentObject::DrawImgui();

#endif // _DEBUG
}

void Player::PlayerMove()
{
	D3DXVECTOR3 forward = GetForward();



	//	プレイヤー移動処理
	if (GetKeyboardPress(DIK_W)) {

		m_VelocityCom->m_Velocity.z += PLAYER_SPEED * forward.z;
		m_VelocityCom->m_Velocity.x += PLAYER_SPEED * forward.x;
	}
	if (GetKeyboardPress(DIK_S)) {
		m_VelocityCom->m_Velocity.z -= PLAYER_SPEED * forward.z;
		m_VelocityCom->m_Velocity.x -= PLAYER_SPEED * forward.x;
	}
	if (GetKeyboardPress(DIK_A)) {
		m_VelocityCom->m_Velocity.z += PLAYER_SPEED * GetLeft().z;
		m_VelocityCom->m_Velocity.x += PLAYER_SPEED * GetLeft().x;
	}
	if (GetKeyboardPress(DIK_D)) {
		m_VelocityCom->m_Velocity.z += PLAYER_SPEED * GetRight().z;
		m_VelocityCom->m_Velocity.x += PLAYER_SPEED * GetRight().x;
	}

	if (m_IsUseBullet) 
	{		
		float speedup = 3.0f;

		//	プレイヤー移動処理
		if (GetKeyboardPress(DIK_W)) {

			m_VelocityCom->m_Velocity.z += PLAYER_SPEED * forward.z * speedup;
			m_VelocityCom->m_Velocity.x += PLAYER_SPEED * forward.x * speedup;
		}
		if (GetKeyboardPress(DIK_S)) {
			m_VelocityCom->m_Velocity.z -= PLAYER_SPEED * forward.z * speedup;
			m_VelocityCom->m_Velocity.x -= PLAYER_SPEED * forward.x * speedup;
		}
		if (GetKeyboardPress(DIK_A)) {
			m_VelocityCom->m_Velocity.z += PLAYER_SPEED * GetLeft().z * speedup;
			m_VelocityCom->m_Velocity.x += PLAYER_SPEED * GetLeft().x * speedup;
		}
		if (GetKeyboardPress(DIK_D)) {
			m_VelocityCom->m_Velocity.z += PLAYER_SPEED * GetRight().z * speedup;
			m_VelocityCom->m_Velocity.x += PLAYER_SPEED * GetRight().x * speedup;
		}


		if (GetKeyboardPress(DIK_I) || GetKeyboardPress(DIK_SPACE)) {
			
			m_VelocityCom->m_Velocity.y += PLAYER_SPEED * speedup;
		}
		if (GetKeyboardPress(DIK_K) || GetKeyboardPress(DIK_LSHIFT)) {			
			m_VelocityCom->m_Velocity.y -= PLAYER_SPEED * speedup;
		}
	}
	else
	{
		//	重力	
		m_VelocityCom->m_Velocity.y -= GRAVITY;
	}

	static int counter = 0;

	if (counter % 2 == 0) {


		float length = D3DXVec3Length(&m_VelocityCom->m_Velocity);

		if (length >= 0.03f &&
			length < 0.06f) {
			SetParticle({0.0f,1.0f,1.0f,0.5f});
		}
		else if (length >= 0.06f &&
			length < 0.15f) 
		{
			for (int i = 0; i < 2; i++)
				SetParticle({ 0.0f,1.0f,1.0f,0.75f });

		}
		else if(length >= 0.15f)
		{
			for (int i = 0; i < 5; i++)
				SetParticle({ 0.0f,1.0f,1.0f,1.0f });
		}
	}

	
	counter++;
					

	//	減衰	
	m_VelocityCom->m_Velocity.x *= ATTENUATION.x;	
	if (m_IsUseBullet) {
		m_VelocityCom->m_Velocity.y *= 0.9f;
	}
	else {
		m_VelocityCom->m_Velocity.y *= ATTENUATION.y;
	}
	
	m_VelocityCom->m_Velocity.z *= ATTENUATION.z;



	D3DXVECTOR3 oldPos = m_Position;
	float groundHeight = 0.0f;

	std::vector<CO_Stand*> stands = GetComponent<CollisionComponent>()->IsCollisionXAxis<CO_Stand>();
	if (!stands.empty())
	{
		groundHeight = 0.1f * stands[0]->GetScale().y;
		m_Position = oldPos;
	}

	//	接台

	
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



	if (!m_IsUseBullet) {
		//	ジャンプ	
		if (GetKeyboardTrigger(DIK_SPACE) &&
			m_Position.y < groundHeight + 0.1f &&
			m_VelocityCom->m_Velocity.y < 0.1f) {
			for (int i = 0; i < 100; i++)
				SetParticle_Landing();
			m_VelocityCom->m_Velocity.y = JUMP;

			m_SEJump->SetAudioVolume(0.25f);
			m_SEJump->Play(false);
		}
	}

	//	接地	
	if (m_Position.y < groundHeight &&
		m_VelocityCom->m_Velocity.y < 0.0f) {

		if (m_VelocityCom->m_Velocity.y < -0.35f) {
			for(int i=0;i<100;i++)
				SetParticle_Landing();
			m_SELanding->SetAudioVolume(0.4f);
			m_SELanding->Play(false);
		}
		m_Position.y = groundHeight;
		m_VelocityCom->m_Velocity.y = 0;		
		
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

void Player::SetParticle(const D3DXCOLOR& start_col)
{
	PARTICLE par;
	par.acc = { 0.0f,0.0f,0.0f };
	par.m_ColorOverLifeTime_Start = start_col;
	par.m_ColorOverLifeTime_End = { 0.0f,0.0f,0.0f,1.0f };
	par.col = par.m_ColorOverLifeTime_Start;
	par.life = 30;
	par.pos = m_Position +MyMath::VEC3Random(-0.25f,0.25f);
	par.pos.y = m_Position.y;
	par.rot = { 0.0f,0.0f,0.0f };
	par.rot_vel = MyMath::VEC3Random(-0.01f, 0.01f);
	par.m_SizeOverLifeTime_Start = MyMath::Random(0.01f,0.2f);
	par.m_SizeOverLifeTime_End = 0.0f;
	par.size = par.m_SizeOverLifeTime_Start;
	par.status = 0;
	par.type = rand() % PARTICLE_TYPE_MAX;
	par.use = true;
	par.use_torii = false;
	par.vel = MyMath::XZRandom(-0.01f, 0.01f);
	par.vel.y = MyMath::Random(0.01f, 0.1f);
	m_Particle->SetParticle(par);
}

void Player::SetParticle_Landing()
{
	PARTICLE par;
	par.acc = { 0.0f,0.0f,0.0f };
	par.m_ColorOverLifeTime_Start = { 1.0f,1.0f,1.0f,1.0f };
	par.m_ColorOverLifeTime_End = { 0.0f,0.0f,0.0f,1.0f };
	par.col = par.m_ColorOverLifeTime_Start;
	par.life = 60;
	par.pos = m_Position + MyMath::VEC3Random(-0.25f, 0.25f);
	par.pos.y = m_Position.y;
	par.rot = { 0.0f,0.0f,0.0f };
	par.rot_vel = MyMath::VEC3Random(-0.01f, 0.01f);
	par.m_SizeOverLifeTime_Start = MyMath::Random(0.01f, 0.2f);
	par.m_SizeOverLifeTime_End = 0.0f;
	par.size = par.m_SizeOverLifeTime_Start;
	par.status = 0;
	par.type = rand() % PARTICLE_TYPE_MAX;
	par.use = true;
	par.use_torii = false;
	par.vel = MyMath::XZRandom(-0.15f, 0.15f);
	par.vel.y = MyMath::Random(0.01f, 0.05f);
	m_Particle->SetParticle(par);
}
