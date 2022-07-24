#include "ImGuiObject.h"
#include "manager.h"
#include "GameScene.h"
#include "player.h"	



void ImGuiObject::Init()
{
	m_PlayerWindow = true;

	m_Scene = Manager::GetScene();
	m_Player = m_Scene->GetGameObject<Player>();
}

void ImGuiObject::Uninit()
{
}

void ImGuiObject::Update()
{
}

void ImGuiObject::Draw()
{
#ifdef _DEBUG
	
	ImGui::Begin("Player Window", &m_PlayerWindow);

	
	D3DXVECTOR3 ppos = m_Player->GetPosition();	
	float fpos[3] = { ppos.x,ppos.y,ppos.z };
	ImGui::SliderFloat3("Player Position",
		fpos, -100.0f, 100.0f, "%.3f", 1.0f);
	m_Player->SetPosition(fpos);

	

	ImGui::End();	
#endif // _DEBUG
}
