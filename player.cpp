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

void Player::Init()
{	
	m_Model = new Model();
	m_Model->Load(texName);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");

	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(scale, scale, scale);
}

void Player::Uninit()
{
	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Player::Update()
{
	if (GetKeyboardPress(DIK_W)) {
		m_Position.z += PLAYER_SPEED;
	}
	if (GetKeyboardPress(DIK_S)) {
		m_Position.z -= PLAYER_SPEED;
	}

	if (GetKeyboardPress(DIK_A)) {
		m_Position.x -= PLAYER_SPEED;
	}
	if (GetKeyboardPress(DIK_D)) {
		m_Position.x += PLAYER_SPEED;
	}

	//if (GetKeyboardTrigger(DIK_SPACE)) {
	if (GetKeyboardPress(DIK_SPACE)) {
		Scene* scene = Manager::GetScene();
		scene->AddGameObject<Bullet>(LAYER_3D)->SetPosition(m_Position);
	}	

	//	エネミー取得
	Scene* scene = Manager::GetScene();
	std::vector<item*> itemList
		= scene->GetGameObjects<item>();

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
