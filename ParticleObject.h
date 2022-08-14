#pragma once
#include "ComponentObject.h"
#include "scene.h"
#include "manager.h"
#include "camera.h"
#include "model_variable.h"
enum PARTICLE_MODEL_TYPE {
	PARTICLE_TYPE_NORMAL,
	PARTICLE_TYPE_CUBE,
	PARTICLE_TYPE_SPHERE,
	PARTICLE_TYPE_MAX
};
struct PARTICLE
{
	int		status;		// ���
	int		type;
	D3DXVECTOR3	pos;		// �ʒu
	D3DXVECTOR3	vel;		// ���x
	D3DXVECTOR3	acc;		// �����x
	D3DXVECTOR3 rot;	//	��]	
	D3DXVECTOR3 rot_vel;
	float	size;		// �傫��
	int		life;		// ���Ŏ���(�t���[����)
	bool    use;	

	D3DXCOLOR col;		// �F

	D3DXCOLOR m_ColorOverLifeTime_Start = { 1.0f,1.0f,1.0f,1.0f };
	D3DXCOLOR m_ColorOverLifeTime_End = { 0.0f,0.0f,0.0f,0.0f };

	float m_SizeOverLifeTime_Start = 0.0f;
	float m_SizeOverLifeTime_End = 1.0f;
};
class ParticleObject :
    public ComponentObject
{
private:
	inline static const int PARTICLE_MAX = 1000;
	std::vector<PARTICLE> m_Particles;

	
	std::shared_ptr<Model_variable> m_Model;
	std::shared_ptr<Model_variable> m_Model_Cube;
	std::shared_ptr<Model_variable> m_Model_Sphere;

	std::shared_ptr <VertexShader> m_VertexShader;
	std::shared_ptr<PixelShader> m_PixelShader;

	std::string m_ModelName = "asset\\model\\particle_object.obj";
	std::string m_ModelName_Cube = "asset\\model\\particle_object_cube.obj";
	std::string m_ModelName_Sphere = "asset\\model\\particle_object_sphere.obj";

	float m_Random_Min = -0.1f;
	float m_Random_Max = 0.1f;

	Camera* m_Camera;
public:    
	void SetModelName(const std::string& name) { m_ModelName = name; }

    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

	virtual void DrawImgui()override;

	//	���S�����_���ȐF
	void SetParticle_Preset1();	
	void SetParticle_Preset1(const D3DXVECTOR3& position);

	//	�`��
	void SetParticle_Preset2(const D3DXVECTOR3& position);

	//	�S����
	//	�����灪�ɏ������Ȃ��Ă���
	void SetParticle_Preset3(const float& area);

//	SetParticles �Q---------------------------------------
	void SetParticles(const D3DXVECTOR3& velocity);

	void SetParticles(const D3DXVECTOR3& pos,
		const D3DXVECTOR3& velocity);

	void SetParticles(const D3DXVECTOR3& pos,
		const D3DXVECTOR3& velocity,
		const int& life);

	void SetParticles(const D3DXVECTOR3& pos,
		const D3DXVECTOR3& velocity,
		const int& life,
		const D3DXCOLOR& start_col,
		const D3DXCOLOR& end_col);

	void SetParticles(const D3DXVECTOR3& pos,
		const D3DXVECTOR3& velocity,
		const D3DXVECTOR3& rotation_velocity,
		const int& life,
		const D3DXCOLOR& start_col,
		const D3DXCOLOR& end_col);

	void SetParticles(const D3DXVECTOR3& pos,
		const D3DXVECTOR3& velocity,
		const D3DXVECTOR3& rotation_velocity,
		const int& life,
		const int& type,
		const D3DXCOLOR& start_col,
		const D3DXCOLOR& end_col);

	void SetParticles(const D3DXVECTOR3& pos,
		const D3DXVECTOR3& velocity,
		const D3DXVECTOR3& rotation_velocity,
		const int& life,
		const int& type,
		const D3DXCOLOR& start_col,
		const D3DXCOLOR& end_col,
		const float& start_size,
		const float& end_size);

};

