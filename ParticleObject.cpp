#include "ParticleObject.h"
#include "ResourceManager.h"
#include "VertexInitialize.h"

void ParticleObject::Init()
{

	m_Model = ResourceManger<Model_variable>::GetResource(m_ModelName.c_str());

	m_VertexShader =
		ResourceManger<VertexShader>::GetResource(VertexShader::UNLIT_VERTEX_SHADER.c_str());
	m_PixelShader =
		ResourceManger<PixelShader>::GetResource(PixelShader::UNLIT_PIXEL_SHADER.c_str());


	std::shared_ptr<Scene> scene = Manager::GetScene();
	m_Camera = scene->GetGameObject<Camera>();

	m_Particles.resize(PARTICLE_MAX);
	for (int i = 0; i < m_Particles.size(); i++) {
		m_Particles[i].status = 0;
		m_Particles[i].pos = { 0.0f,0.0f,0.0f };
		m_Particles[i].vel = { 0.0f,-0.5f,0.0f };
		m_Particles[i].rot = { 0.0f,0.0f,0.0f };
		m_Particles[i].acc = { 0.0f,0.1f,0.0f };
		m_Particles[i].size = m_SizeOverLifeTime_Start;
		m_Particles[i].use = false;
		m_Particles[i].col = m_SizeOverLifeTime_Start;
	}
}

void ParticleObject::Uninit()
{

}

void ParticleObject::Update()
{
	if (GetKeyboardPress(DIK_T))
	{

	}

	for (int i = 0; i < m_Particles.size(); i++) {		
		//	寿命で終了
		if (m_Particles[i].status >= m_Particles[i].life)
		{
			m_Particles[i].use = false;
			m_Particles[i].status = 0;
		}


		//	使われていなかったら戻る
		if (!m_Particles[i].use) continue;
		
		//	加速度
		m_Particles[i].vel += m_Particles[i].acc;

		//	速度
		m_Particles[i].pos += m_Particles[i].vel;

		//	寿命に応じた色
		D3DXColorLerp(&m_Particles[i].col,
			&m_ColorOverLifeTime_Start,
			&m_ColorOverLifeTime_End,
			(float)m_Particles[i].status / (float)m_Particles[i].life);
		
		//	寿命測定
		m_Particles[i].status++;
	}
}

void ParticleObject::Draw()
{
	//	シェーダ
	m_VertexShader->Draw();
	m_PixelShader->Draw();

	for (int i = 0; i < m_Particles.size(); i++)
	{
		if (!m_Particles[i].use)continue;

		//ワールドマトリクス設定
		D3DXMATRIX world, scale, rot, trans;
		D3DXMatrixScaling(&scale,
			m_Particles[i].pos.x,
			m_Particles[i].pos.y,
			m_Particles[i].pos.z);
		D3DXMatrixRotationYawPitchRoll(&rot,
			m_Particles[i].rot.x,
			m_Particles[i].rot.y,
			m_Particles[i].rot.z);
		D3DXMatrixTranslation(&trans,
			m_Particles[i].size,
			m_Particles[i].size,
			m_Particles[i].size);
		world = scale * rot * trans;
		Renderer::SetWorldMatrix(&world);


		m_Model->SetDiffuse(m_Particles[i].col);

		Renderer::SetAlphaToCoverage(true);
		m_Model->Draw();
		Renderer::SetAlphaToCoverage(false);

	}

	
}

void ParticleObject::DrawImgui()
{
	ImGui::Begin("ParticleObject");

	ImGui::Text("ModelName:%s", m_ModelName.c_str());

	//	ColorOverLifeTime_Start
	//	できるかは、わからない。
	{
		ImVec4 color = { 1.0f,1.0f,1.0f,1.0f };
		MyMath::FromD3DXCOLORToImVec4(&color, m_ColorOverLifeTime_Start);
		ImGui::ColorEdit4("COLT_Start", (float*)&color);
		MyMath::FromImVec4ToD3DXCOLOR(&m_ColorOverLifeTime_Start, color);
	}

	//	ColorOverLifeTime_Start
//	できるかは、わからない。
	{
		ImVec4 color = { 1.0f,1.0f,1.0f,1.0f };
		MyMath::FromD3DXCOLORToImVec4(&color, m_ColorOverLifeTime_End);
		ImGui::ColorEdit4("COLT_End", (float*)&color);
		MyMath::FromImVec4ToD3DXCOLOR(&m_ColorOverLifeTime_End, color);
	}

	ImGui::End();
}
