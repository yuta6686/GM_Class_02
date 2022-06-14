#include "main.h"
#include "renderer.h"
#include "model.h"
#include "player.h"
#include "Bullet.h"
#include "manager.h"
#include "scene.h"

#define PLAYER_SPEED 0.25f

static char texName[] = { "asset\\model\\torii.obj" };
static float scale = 0.5f;

static Scene* g_Scene;


void Player::Init()
{	
	m_Model = ResourceManger<Model>::GetResource(texName);
	

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");

	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(scale, scale, scale);

	g_Scene = Manager::GetScene();
}

void Player::Uninit()
{
	

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Player::Update()
{		
	//	プレイヤー移動処理
	PlayerMove();
	
	//	プレイヤー回転処理
	PlayerRotation();

	//	バレット撃つ処理
	ShootBullet();

	//	アイテム取得	
	GetItem();

//#ifdef _DEBUG
//	char* str = GetDebugStr();
//	wsprintf(GetDebugStr(), "game");
//	wsprintf(&str[strlen(str)], "Position.x: %d y:%d z:%d",
//		(int)m_Position.x,
//		(int)m_Position.y,
//		(int)m_Position.z);
//
//	SetWindowText(GetWindow(), GetDebugStr());
//#endif
}

void Player::Draw()
{
	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	////シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();
}

void Player::PlayerMove()
{
	D3DXVECTOR3 forward = GetForward();

	//	プレイヤー移動処理
	if (GetKeyboardPress(DIK_W)) {
		m_Position.z += PLAYER_SPEED * forward.z;
		m_Position.x += PLAYER_SPEED * forward.x;
	}
	if (GetKeyboardPress(DIK_S)) {
		m_Position.z -= PLAYER_SPEED * forward.z;
		m_Position.x -= PLAYER_SPEED * forward.x;
	}

	if (GetKeyboardPress(DIK_A)) {
		m_Position.z += PLAYER_SPEED * GetLeft().z;
		m_Position.x += PLAYER_SPEED * GetLeft().x;
	}
	if (GetKeyboardPress(DIK_D)) {
		m_Position.z += PLAYER_SPEED * GetRight().z;
		m_Position.x += PLAYER_SPEED * GetRight().x;
	}
	

}

void Player::PlayerRotation()
{
	if (GetKeyboardPress(DIK_I)) {
		m_CameraRot.y += PLAYER_SPEED / 5;
	}

	if (GetKeyboardPress(DIK_K)) {
		m_CameraRot.y -= PLAYER_SPEED / 5;
	}

	if (IsMouseRightPressed()) {
		m_CameraRot.y += GetMouseX() / 100.0f;

		if (m_CameraRot.x > GetRadian(60.0f)) {
			m_CameraRot.x = GetRadian(60.0f);
		}
		else if (m_CameraRot.x < GetRadian(-60.0f)) {
			m_CameraRot.x = GetRadian(-60.0f);
		}
		else {
			m_CameraRot.x += GetMouseY() / 100.0f;
		}

	}

	m_Rotation = m_CameraRot;
	m_Rotation.x = 0.0f;
	
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

void Player::ShootBullet()
{
	if (IsMouseLeftPressed()) {
		//	バレット生成
		Bullet* obj = g_Scene->AddGameObject<Bullet>(LAYER_3D);

		//	回転調整
		D3DXVECTOR3 rot = m_CameraRot, rrot = rot;
		rot.x = rrot.y;
		rot.y = rrot.x;
		rot.z = rrot.z;

		//	セット
		obj->SetPosition(m_Position);
		obj->SetRotation(rot);
		obj->SetForward(GetCameraForward());
	}
}
