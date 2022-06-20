#include "main.h"
#include "renderer.h"
#include "polygon2D.h"
#include "field.h"
#include "model.h"
#include "input.h"
#include "bullet.h"
#include "scene.h"
#include "manager.h"
#include "ResourceManager.h"
#include "effect_explosion.h"
#include "player.h"
#include "Enemy.h"

void Bullet::Init()
{
	//m_Model = ModelManager::GetModel("asset\\model\\arrow.obj");
	m_Model = ResourceManger<Model>::GetResource("asset\\model\\arrow.obj");
	

	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.2f, 1.2f, 1.2f);


	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");

}

void Bullet::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Bullet::Update()
{
	std::shared_ptr<Scene> scene = Manager::GetScene();

	Player* player = scene->GetGameObject<Player>();


	//m_Position.z += BULLET_SPEED_MAX;
	m_Position += m_Forward * BULLET_SPEED_MAX;
	//m_Rotation = player->GetForward();

	if (m_Position.z > 100.0f || 
		m_Position.z < -100.0f ||
		m_Position.x > 100.0f ||
		m_Position.x < -100.0f)
	{
		SetDestroy();
		return;
	}

	//	エネミー取得	
	std::vector<Enemy*> enemyList
		= scene->GetGameObjects<Enemy>();

	for (auto enemy : enemyList) {
		D3DXVECTOR3 enemyPosition = enemy->GetPosition();
		D3DXVECTOR3 direction = m_Position - enemyPosition;
		float length = D3DXVec3Length(&direction);

		if (length < 2.0f) {
			enemy->CollosionWithBullet();
			this->SetDestroy();
			scene->AddGameObject<Effect_explosion>(LAYER_3D)->SetPosition(m_Position);
			return;
		}
	}


}

void Bullet::Draw()
{
	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);


	//シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);


	//ワールドマトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.x, m_Rotation.y, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);


	m_Model->Draw();
}
