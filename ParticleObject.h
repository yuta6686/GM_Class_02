#pragma once
#include "ComponentObject.h"
#include "scene.h"
#include "manager.h"
#include "camera.h"
#include "model_variable.h"
struct PARTICLE
{
	int		status;		// ���
	D3DXVECTOR3	pos;		// �ʒu
	D3DXVECTOR3	vel;		// ���x
	D3DXVECTOR3	acc;		// �����x
	D3DXVECTOR3 rot;	//	��]	
	float	size;		// �傫��
	int		life;		// ���Ŏ���(�t���[����)
	bool    use;	

	D3DXCOLOR col;		// �F
};
class ParticleObject :
    public ComponentObject
{
private:
	inline static const int PARTICLE_MAX = 1000;
	std::vector<PARTICLE> m_Particles;

	std::shared_ptr<Model_variable> m_Model;
	std::shared_ptr <VertexShader> m_VertexShader;
	std::shared_ptr<PixelShader> m_PixelShader;

	std::string m_ModelName = "asset\\model\\";

	D3DXCOLOR m_ColorOverLifeTime_Start = { 1.0f,1.0f,1.0f,1.0f };
	D3DXCOLOR m_ColorOverLifeTime_End = { 0.0f,0.0f,0.0f,0.0f };

	float m_SizeOverLifeTime_Start = 0.0f;
	float m_SizeOverLifeTime_End = 10.0f;

	Camera* m_Camera;
public:    
	void SetModelName(const std::string& name) { m_ModelName = name; }
	//	void SetParameter();
	void SetColorOverLifeTime(
		const D3DXCOLOR& start,
		const D3DXCOLOR& end) {
		m_ColorOverLifeTime_Start = start;
		m_ColorOverLifeTime_End = end;
	}

	void SetParticles(const D3DXVECTOR3& velocity)
	{
		for (int i = 0; i < m_Particles.size(); i++) {
			m_Particles[i].status = 0;
			m_Particles[i].pos = { 0.0f,0.0f,0.0f };
			m_Particles[i].vel = velocity;
			m_Particles[i].rot = { 0.0f,0.0f,0.0f };
			m_Particles[i].acc = { 0.0f,0.1f,0.0f };
			m_Particles[i].size = m_SizeOverLifeTime_Start;
			m_Particles[i].use = true;
			m_Particles[i].col = m_SizeOverLifeTime_Start;
		}
	}

	void SetParticles(const D3DXVECTOR3& pos,
		const D3DXVECTOR3& velocity)
	{
		for (int i = 0; i < m_Particles.size(); i++) {
			m_Particles[i].status = 0;
			m_Particles[i].pos = pos;
			m_Particles[i].vel = velocity;
			m_Particles[i].rot = { 0.0f,0.0f,0.0f };
			m_Particles[i].acc = { 0.0f,0.1f,0.0f };
			m_Particles[i].size = m_SizeOverLifeTime_Start;
			m_Particles[i].use = true;
			m_Particles[i].col = m_SizeOverLifeTime_Start;
		}
	}

    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

	virtual void DrawImgui()override;
};

