#include "ParticleObject.h"
#include "ResourceManager.h"
#include "VertexInitialize.h"
#include "manager.h"
#include "player.h"
#include <sstream>


void ParticleObject::Init()
{

	m_Model = ResourceManger<Model_variable>::GetResource(m_ModelName.c_str());
	m_Model_Cube = ResourceManger<Model_variable>::GetResource(m_ModelName_Cube.c_str());
	m_Model_Sphere = ResourceManger<Model_variable>::GetResource(m_ModelName_Sphere.c_str());

	for (int i = 1; i <= 50; i++)
	{
		std::ostringstream oss;
		if (i <= 9) {
			oss << 0 << 0;
		}
		else if (i >= 10) {
			oss << 0;
		}
		
		oss << i;
		m_Torii_Broken.push_back(ResourceManger<Model_variable>::GetResource(m_ModelName_Torii.c_str() + oss.str() + m_Obj.c_str()));
	}

	m_VertexShader =
		ResourceManger<VertexShader>::GetResource(VertexShader::UNLIT_VERTEX_SHADER.c_str());
	m_PixelShader =
		ResourceManger<PixelShader>::GetResource(PixelShader::UNLIT_PIXEL_SHADER.c_str());


	std::shared_ptr<Scene> scene = Manager::GetScene();
	m_Camera = scene->GetGameObject<Camera>();

	m_Particles.resize(PARTICLE_MAX);
	for (unsigned int i = 0; i < m_Particles.size(); i++) {
		m_Particles[i].status = 0;
		m_Particles[i].pos = { 0.0f,0.0f,0.0f };
		m_Particles[i].vel = { 0.0f,-0.5f,0.0f };
		m_Particles[i].rot = { 0.0f,0.0f,0.0f };
		m_Particles[i].acc = { 0.0f,0.1f,0.0f };
		m_Particles[i].m_SizeOverLifeTime_Start = 0.0f;
		m_Particles[i].m_SizeOverLifeTime_End = 1.0f;
		m_Particles[i].size = m_Particles[i].m_SizeOverLifeTime_Start;
		m_Particles[i].use = false;
		m_Particles[i].col = m_Particles[i].m_ColorOverLifeTime_Start;
		
		
	}
}

void ParticleObject::Uninit()
{

}

void ParticleObject::Update()
{


	for (unsigned int i = 0; i < m_Particles.size(); i++) {
		//	�����ŏI��
		if (m_Particles[i].status >= m_Particles[i].life)
		{
			m_Particles[i].use = false;
			m_Particles[i].status = 0;
		}


		//	�g���Ă��Ȃ�������߂�
		if (!m_Particles[i].use) continue;
		
		//	�����x
		m_Particles[i].vel += m_Particles[i].acc;

		//	���x
		m_Particles[i].pos += m_Particles[i].vel;

		//	��]���x
		m_Particles[i].rot += m_Particles[i].rot_vel;

		//	�����ɉ������F
		D3DXColorLerp(&m_Particles[i].col,
			&m_Particles[i].m_ColorOverLifeTime_Start,
			&m_Particles[i].m_ColorOverLifeTime_End,
			(float)m_Particles[i].status / (float)m_Particles[i].life);

		//	�����ɉ������T�C�Y
		MyMath::FloatLerp(&m_Particles[i].size,
			&m_Particles[i].m_SizeOverLifeTime_Start,
			&m_Particles[i].m_SizeOverLifeTime_End,
			powf((float)m_Particles[i].status / (float)m_Particles[i].life,2.0f));
		
		//	��������
		m_Particles[i].status++;
	}
}

void ParticleObject::Draw()
{
	//	�V�F�[�_
	m_VertexShader->Draw();
	m_PixelShader->Draw();

	for (unsigned int i = 0; i < m_Particles.size(); i++)
	{
		if (!m_Particles[i].use)continue;

		//���[���h�}�g���N�X�ݒ�
		D3DXMATRIX world, scale, rot, trans;
		D3DXMatrixScaling(&scale,
			m_Particles[i].size,
			m_Particles[i].size,
			m_Particles[i].size);
		D3DXMatrixRotationYawPitchRoll(&rot,
			m_Particles[i].rot.x,
			m_Particles[i].rot.y,
			m_Particles[i].rot.z);
		D3DXMatrixTranslation(&trans, 
			m_Particles[i].pos.x,
			m_Particles[i].pos.y,
			m_Particles[i].pos.z
		);
		world = scale * rot * trans;
		Renderer::SetWorldMatrix(&world);


		

		Renderer::SetAddBlend(true);

		if (m_Particles[i].use_torii) 
		{
			m_Torii_Broken[m_Particles[i].type]->Draw();
		}
		else
		{
			switch (m_Particles[i].type)
			{
			case PARTICLE_TYPE_NORMAL:
				m_Model->SetDiffuse(m_Particles[i].col);

				m_Model->Draw();
				break;
			case PARTICLE_TYPE_CUBE:
				m_Model_Cube->SetDiffuse(m_Particles[i].col);

				m_Model_Cube->Draw();
				break;
			case PARTICLE_TYPE_SPHERE:
				m_Model_Sphere->SetDiffuse(m_Particles[i].col);

				m_Model_Sphere->Draw();
				break;
			default:
				m_Model->SetDiffuse(m_Particles[i].col);

				m_Model->Draw();
				break;
			}
		}
		
		Renderer::SetAddBlend(false);

	}

	
}

void ParticleObject::DrawImgui()
{
	ImGui::Begin("ParticleObject");

	ImGui::Text("ModelName:%s", m_ModelName.c_str());


	ImGui::End();
}

void ParticleObject::SetParticle_Preset1()
{
	D3DXVECTOR3 velocity;

	velocity.x = MyMath::Random(m_Random_Min, m_Random_Max)*2.0f;
	velocity.y = MyMath::Random(m_Random_Min, m_Random_Max)*2.0f;
	velocity.z = MyMath::Random(m_Random_Min, m_Random_Max)*2.0f;

	D3DXVECTOR3 rot_velocity;

	rot_velocity.x = MyMath::Random(m_Random_Min, m_Random_Max);
	rot_velocity.y = MyMath::Random(m_Random_Min, m_Random_Max);
	rot_velocity.z = MyMath::Random(m_Random_Min, m_Random_Max);

	D3DXVECTOR3 position;
	std::shared_ptr<Scene> scene = Manager::GetScene();
	position = scene->GetGameObject<Player>()->GetPosition();

	D3DXCOLOR start_color;
	start_color.r = MyMath::Random(0.5f, 1.0f);
	start_color.g = MyMath::Random(0.5f, 1.0f);
	start_color.b = MyMath::Random(0.5f, 1.0f);
	start_color.a = 1.0f;

	D3DXCOLOR end_color;
	end_color.r = MyMath::Random(0.0f, 1.0f);
	end_color.g = MyMath::Random(0.0f, 1.0f);
	end_color.b = MyMath::Random(0.0f, 1.0f);
	end_color.a = 0.5f;

	float start_size = MyMath::Random(0.0f, 1.0f);
	float end_size = MyMath::Random(0.0f, 1.0f);

	int type = rand() % PARTICLE_TYPE_MAX;

	SetParticles(position, velocity, rot_velocity, 120,type, start_color, end_color,start_size,end_size);
}

void ParticleObject::SetParticle_Preset1(const D3DXVECTOR3& position)
{
	D3DXVECTOR3 velocity;

	velocity.x = MyMath::Random(-0.5f,0.5f);
	velocity.y = MyMath::Random(-0.5f,0.5f);
	velocity.z = MyMath::Random(-0.5f,0.5f);

	D3DXVECTOR3 rot_velocity;

	rot_velocity.x = MyMath::Random(m_Random_Min, m_Random_Max);
	rot_velocity.y = MyMath::Random(m_Random_Min, m_Random_Max);
	rot_velocity.z = MyMath::Random(m_Random_Min, m_Random_Max);

	D3DXCOLOR start_color;
	start_color.r = MyMath::Random(0.5f, 1.0f);
	start_color.g = MyMath::Random(0.5f, 1.0f);
	start_color.b = MyMath::Random(0.5f, 1.0f);
	start_color.a = 1.0f;

	D3DXCOLOR end_color;
	end_color.r = MyMath::Random(0.0f, 1.0f);
	end_color.g = MyMath::Random(0.0f, 1.0f);
	end_color.b = MyMath::Random(0.0f, 1.0f);
	end_color.a = 0.5f;

	float start_size = MyMath::Random(0.0f, 0.8f);
	float end_size = MyMath::Random(0.0f, 0.2f);

	int type = rand() % PARTICLE_TYPE_MAX;

	SetParticles(position, velocity, rot_velocity, 60, type, start_color, end_color,start_size,end_size);
}

void ParticleObject::SetParticle_Preset2(const D3DXVECTOR3& position)
{
	D3DXVECTOR3 velocity;

	velocity.x = MyMath::Random(m_Random_Min, m_Random_Max);
	velocity.y = MyMath::Random(m_Random_Min, m_Random_Max);
	velocity.z = MyMath::Random(m_Random_Min, m_Random_Max);

	D3DXVECTOR3 rot_velocity;

	rot_velocity.x = MyMath::Random(m_Random_Min, m_Random_Max);
	rot_velocity.y = MyMath::Random(m_Random_Min, m_Random_Max);
	rot_velocity.z = MyMath::Random(m_Random_Min, m_Random_Max);

	D3DXCOLOR start_color;
	start_color.r = MyMath::Random(0.0f, 0.5f);
	start_color.g = MyMath::Random(0.5f, 1.0f);
	start_color.b = MyMath::Random(0.5f, 1.0f);
	start_color.a = 1.0f;

	D3DXCOLOR end_color;
	end_color.r = MyMath::Random(0.0f, 0.5f);
	end_color.g = MyMath::Random(0.5f, 1.0f);
	end_color.b = MyMath::Random(0.5f, 1.0f);
	end_color.a = 0.5f;

	float start_size = MyMath::Random(0.0f, 0.8f);
	float end_size = MyMath::Random(0.0f, 0.2f);

	int type = rand() % PARTICLE_TYPE_MAX;

	SetParticles(position, velocity, rot_velocity, 120, type, start_color, end_color,start_size,end_size);
}

void ParticleObject::SetParticle_Preset3(const float& area)
{
	D3DXVECTOR3 position = MyMath::XZRandom(-area, area);
	position.y = -3.0f;

	D3DXVECTOR3 velocity;

	velocity.x = MyMath::Random(-0.1f, 0.1f);
	velocity.y = MyMath::Random(0.0f, 0.1f);
	velocity.z = MyMath::Random(-0.1f, 0.1f);

	D3DXVECTOR3 rot_velocity;

	rot_velocity.x = MyMath::Random(0.0f, 0.0f);
	rot_velocity.y = MyMath::Random(0.0f, 0.0f);
	rot_velocity.z = MyMath::Random(0.0f, 0.0f);

	D3DXCOLOR start_color;
	start_color.r = MyMath::Random(0.0f, 0.0f);
	start_color.g = MyMath::Random(0.0f, 1.0f);
	start_color.b = MyMath::Random(0.0f, 1.0f);
	start_color.a = MyMath::Random(0.0f, 0.6f);

	D3DXCOLOR end_color;
	end_color.r =0.0f;
	end_color.g =0.0f;
	end_color.b =0.0f;
	end_color.a = 0.5f;

	float start_size = MyMath::Random(0.0f, 0.55f);
	float end_size = 0.0f;

	int type = rand() % PARTICLE_TYPE_MAX;

	SetParticles(position, velocity, rot_velocity, 500, type, start_color, end_color, start_size, end_size);
}

void ParticleObject::SetParticle_ToriiBloken_Rising()
{
	PARTICLE par;
	par.acc = { 0.0f,0.0f,0.0f };
	par.m_ColorOverLifeTime_Start = { 1.0f,1.0f,1.0f,0.7f };
	par.m_ColorOverLifeTime_End = { 1.0f,1.0f,1.0f,0.5f };
	par.col = par.m_ColorOverLifeTime_Start;
	par.life = 180;	
	par.pos = MyMath::XZRandom(-50.0f, 50.0f);
	par.pos.y = -0.1f;
	par.rot = { 0.0f,0.0f,0.0f };
	par.rot_vel = MyMath::VEC3Random(-0.01f, 0.01f);
	par.m_SizeOverLifeTime_Start = 2.0f;
	par.m_SizeOverLifeTime_End = 0.0f;
	par.size = par.m_SizeOverLifeTime_Start;
	par.status = 0;
	par.type = rand() % m_Torii_Broken.size();
	par.use = true;
	par.use_torii = true;
	par.vel = MyMath::XZRandom(-0.01f, 0.01f);
	par.vel.y = MyMath::Random(0.01f, 0.2f);

	SetParticle(par);
}

void ParticleObject::SetParticle_Title()
{
	PARTICLE par;
	par.acc = { 0.0f,0.0f,0.0f };
	par.m_ColorOverLifeTime_Start = { 1.0f,0.3f,0.3f,MyMath::Random(0.0f,1.0f) };
	par.m_ColorOverLifeTime_End = { 0.0f,1.0f,1.0f,0.5f };
	par.col = par.m_ColorOverLifeTime_Start;
	par.life = 240;
	par.pos = MyMath::XZRandom(-100.0f, 100.0f);
	par.pos.y = -50.0f;
	par.rot = { 0.0f,0.0f,0.0f };
	par.rot_vel = MyMath::VEC3Random(-0.01f, 0.01f);
	par.m_SizeOverLifeTime_Start = MyMath::Random(0.1f, 2.0f);
	par.m_SizeOverLifeTime_End = 0.0f;
	par.size = par.m_SizeOverLifeTime_Start;
	par.status = 0;
	par.type = PARTICLE_TYPE_SPHERE;
	par.use = true;
	par.use_torii = false;
	par.vel = MyMath::XZRandom(-0.01f, 0.01f);
	par.vel.y = MyMath::Random(0.1f, 0.5f);

	SetParticle(par);
}

void ParticleObject::SetParticles(const D3DXVECTOR3& velocity)
{
	for (unsigned int i = 0; i < m_Particles.size(); i++) {
		if (m_Particles[i].use)continue;
		m_Particles[i].status = 0;
		m_Particles[i].pos = { 0.0f,0.0f,0.0f };
		m_Particles[i].vel = velocity;
		m_Particles[i].rot = { 0.0f,0.0f,0.0f };
		m_Particles[i].rot_vel = { 0.0f,0.0f,0.0f };
		m_Particles[i].acc = { 0.0f,0.0f,0.0f };
		m_Particles[i].m_SizeOverLifeTime_Start = 0.0f;
		m_Particles[i].m_SizeOverLifeTime_End = 1.0f;
		m_Particles[i].size = m_Particles[i].m_SizeOverLifeTime_Start;
		m_Particles[i].use = true;
		m_Particles[i].col = m_Particles[i].m_ColorOverLifeTime_Start;
		m_Particles[i].life = 60;
		break;
	}
}
void ParticleObject::SetParticles(const D3DXVECTOR3& pos, const D3DXVECTOR3& velocity)
{
	for (unsigned int i = 0; i < m_Particles.size(); i++) {
		if (m_Particles[i].use)continue;
		m_Particles[i].status = 0;
		m_Particles[i].pos = pos;
		m_Particles[i].vel = velocity;
		m_Particles[i].rot = { 0.0f,0.0f,0.0f };
		m_Particles[i].rot_vel = { 0.0f,0.0f,0.0f };
		m_Particles[i].acc = { 0.0f,0.0f,0.0f };
		m_Particles[i].m_SizeOverLifeTime_Start = 0.0f;
		m_Particles[i].m_SizeOverLifeTime_End = 1.0f;
		m_Particles[i].size = m_Particles[i].m_SizeOverLifeTime_Start;
		m_Particles[i].use = true;
		m_Particles[i].m_ColorOverLifeTime_Start = { 1.0f,1.0f,1.0f,1.0f };
		m_Particles[i].m_ColorOverLifeTime_End = { 1.0f,1.0f,1.0f,0.0f };
		m_Particles[i].col = m_Particles[i].m_ColorOverLifeTime_Start;
		m_Particles[i].life = 60;
		break;
	}
}
void ParticleObject::SetParticles(const D3DXVECTOR3& pos, const D3DXVECTOR3& velocity, const int& life)
{
	for (unsigned int i = 0; i < m_Particles.size(); i++) {
		if (m_Particles[i].use)continue;
		m_Particles[i].status = 0;
		m_Particles[i].pos = pos;
		m_Particles[i].vel = velocity;
		m_Particles[i].rot = { 0.0f,0.0f,0.0f };
		m_Particles[i].rot_vel = { 0.0f,0.0f,0.0f };
		m_Particles[i].acc = { 0.0f,0.0f,0.0f };
		m_Particles[i].m_SizeOverLifeTime_Start = 0.0f;
		m_Particles[i].m_SizeOverLifeTime_End = 1.0f;
		m_Particles[i].size = m_Particles[i].m_SizeOverLifeTime_Start;
		m_Particles[i].use = true;
		m_Particles[i].m_ColorOverLifeTime_Start = { 1.0f,1.0f,1.0f,1.0f };
		m_Particles[i].m_ColorOverLifeTime_End = { 1.0f,1.0f,1.0f,0.0f };
		m_Particles[i].col = m_Particles[i].m_ColorOverLifeTime_Start;
		m_Particles[i].life = life;
		break;
	}
}
void ParticleObject::SetParticles(const D3DXVECTOR3& pos, const D3DXVECTOR3& velocity, const int& life, const D3DXCOLOR& start_col, const D3DXCOLOR& end_col)
{
	for (unsigned int i = 0; i < m_Particles.size(); i++) {
		if (m_Particles[i].use)continue;
		m_Particles[i].status = 0;
		m_Particles[i].pos = pos;
		m_Particles[i].vel = velocity;
		m_Particles[i].rot = { 0.0f,0.0f,0.0f };
		m_Particles[i].rot_vel = { 0.0f,0.0f,0.0f };
		m_Particles[i].acc = { 0.0f,0.0f,0.0f };
		m_Particles[i].m_SizeOverLifeTime_Start = 0.0f;
		m_Particles[i].m_SizeOverLifeTime_End = 1.0f;
		m_Particles[i].size = m_Particles[i].m_SizeOverLifeTime_Start;
		m_Particles[i].use = true;
		m_Particles[i].m_ColorOverLifeTime_Start = start_col;
		m_Particles[i].m_ColorOverLifeTime_End = end_col;
		m_Particles[i].col = m_Particles[i].m_ColorOverLifeTime_Start;
		m_Particles[i].life = life;
		break;
	}
}
void ParticleObject::SetParticles(const D3DXVECTOR3& pos, const D3DXVECTOR3& velocity, const D3DXVECTOR3& rotation_velocity, const int& life, const D3DXCOLOR& start_col, const D3DXCOLOR& end_col)
{
	for (unsigned int i = 0; i < m_Particles.size(); i++) {
		if (m_Particles[i].use)continue;
		m_Particles[i].status = 0;
		m_Particles[i].pos = pos;
		m_Particles[i].vel = velocity;
		m_Particles[i].rot = { 0.0f,0.0f,0.0f };
		m_Particles[i].rot_vel = rotation_velocity;
		m_Particles[i].acc = { 0.0f,0.0f,0.0f };
		m_Particles[i].m_SizeOverLifeTime_Start = 0.0f;
		m_Particles[i].m_SizeOverLifeTime_End = 1.0f;
		m_Particles[i].size = m_Particles[i].m_SizeOverLifeTime_Start;
		m_Particles[i].use = true;
		m_Particles[i].m_ColorOverLifeTime_Start = start_col;
		m_Particles[i].m_ColorOverLifeTime_End = end_col;
		m_Particles[i].col = m_Particles[i].m_ColorOverLifeTime_Start;
		m_Particles[i].life = life;
		break;
	}
}

void ParticleObject::SetParticles(const D3DXVECTOR3& pos, const D3DXVECTOR3& velocity, const D3DXVECTOR3& rotation_velocity, const int& life, const int& type, const D3DXCOLOR& start_col, const D3DXCOLOR& end_col)
{
	for (unsigned int i = 0; i < m_Particles.size(); i++) {
		if (m_Particles[i].use)continue;
		m_Particles[i].status = 0;
		m_Particles[i].type = type;
		m_Particles[i].pos = pos;
		m_Particles[i].vel = velocity;
		m_Particles[i].rot = { 0.0f,0.0f,0.0f };
		m_Particles[i].rot_vel = rotation_velocity;
		m_Particles[i].acc = { 0.0f,0.0f,0.0f };
		m_Particles[i].m_SizeOverLifeTime_Start = 0.0f;
		m_Particles[i].m_SizeOverLifeTime_End = 1.0f;
		m_Particles[i].size = m_Particles[i].m_SizeOverLifeTime_Start;
		m_Particles[i].use = true;
		m_Particles[i].m_ColorOverLifeTime_Start = start_col;
		m_Particles[i].m_ColorOverLifeTime_End = end_col;
		m_Particles[i].col = m_Particles[i].m_ColorOverLifeTime_Start;
		m_Particles[i].life = life;
		break;
	}
}

void ParticleObject::SetParticles(const D3DXVECTOR3& pos, const D3DXVECTOR3& velocity, const D3DXVECTOR3& rotation_velocity, const int& life, const int& type, const D3DXCOLOR& start_col, const D3DXCOLOR& end_col, const float& start_size, const float& end_size)
{
	for (unsigned int i = 0; i < m_Particles.size(); i++) {
		if (m_Particles[i].use)continue;
		m_Particles[i].status = 0;
		m_Particles[i].type = type;
		m_Particles[i].pos = pos;
		m_Particles[i].vel = velocity;
		m_Particles[i].rot = { 0.0f,0.0f,0.0f };
		m_Particles[i].rot_vel = rotation_velocity;
		m_Particles[i].acc = { 0.0f,0.0f,0.0f };
		m_Particles[i].m_SizeOverLifeTime_Start = start_size;
		m_Particles[i].m_SizeOverLifeTime_End = end_size;
		m_Particles[i].size = m_Particles[i].m_SizeOverLifeTime_Start;
		m_Particles[i].use = true;
		m_Particles[i].m_ColorOverLifeTime_Start = start_col;
		m_Particles[i].m_ColorOverLifeTime_End = end_col;
		m_Particles[i].col = m_Particles[i].m_ColorOverLifeTime_Start;
		m_Particles[i].life = life;
		break;
	}
}

void ParticleObject::SetParticle(const PARTICLE& par)
{
	for (unsigned int i = 0; i < m_Particles.size(); i++) {
		if (m_Particles[i].use)continue;
		m_Particles[i] = par;
		break;
	}
}