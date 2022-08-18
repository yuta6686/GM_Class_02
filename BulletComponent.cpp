#include "BulletComponent.h"
#include "gameObject.h"
#include "manager.h"

void BulletComponent::Init()
{
	m_Particle = Manager::GetScene()->GetGameObject<ParticleObject>();
}

void BulletComponent::Uninit()
{
}

void BulletComponent::Update()
{
	//	‰Á‘¬
	AddParentPos(m_Velocity);

	m_Velocity *= 0.99f;

	
	
	
	//	d—Í
	m_Velocity.y += GRABITY;

	if (m_Particle) {
		PARTICLE par;
		par.acc = { 0.0f,0.0f,0.0f };
		par.m_ColorOverLifeTime_Start = { 0.0f,1.0f,1.0f,0.5f };
		par.m_ColorOverLifeTime_End = { 0.0f,0.0f,0.0f,1.0f };
		par.col = par.m_ColorOverLifeTime_Start;
		par.life = 30;
		par.pos = m_Parent->GetPosition();		
		par.rot = { 0.0f,0.0f,0.0f };
		par.rot_vel = MyMath::VEC3Random(-0.01f, 0.01f);
		par.m_SizeOverLifeTime_Start = 0.5f;
		par.m_SizeOverLifeTime_End = 0.0f;
		par.size = par.m_SizeOverLifeTime_Start;
		par.status = 0;
		par.type = rand() % PARTICLE_TYPE_MAX;
		par.use = true;
		par.use_torii = false;
		par.vel = MyMath::XZRandom(-0.01f, 0.01f);
		par.vel.y = MyMath::Random(0.01f, 0.2f);
		
		m_Particle->SetParticle(par);
	}
}

void BulletComponent::Draw()
{
}

void BulletComponent::DrawImgui()
{
}

void BulletComponent::AddParentPos(D3DXVECTOR3 addvalue)
{
	D3DXVECTOR3 pos = m_Parent->GetPosition();

	m_Parent->SetPosition(pos + addvalue);
}
