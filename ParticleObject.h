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
	int		status = 0;		// 状態
	int		type = 0;
	D3DXVECTOR3	pos = { 0.0f,0.0f,0.0f };		// 位置
	D3DXVECTOR3	vel = { 0.0f,0.0f,0.0f };		// 速度
	D3DXVECTOR3	acc = { 0.0f,0.0f,0.0f };		// 加速度
	D3DXVECTOR3 rot = { 0.0f,0.0f,0.0f };	//	回転	
	D3DXVECTOR3 rot_vel = { 0.0f,0.0f,0.0f };
	float	size = 1.0f;		// 大きさ
	int		life = 60;		// 消滅時間(フレーム数)
	bool    use = false;
	bool	use_torii = false;

	D3DXCOLOR col = { 1.0f,1.0f,1.0f,1.0f };		// 色

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

	std::vector<std::shared_ptr<Model_variable>> m_Torii_Broken;

	std::shared_ptr <VertexShader> m_VertexShader;
	std::shared_ptr<PixelShader> m_PixelShader;

	std::string m_ModelName = "asset\\model\\particle_object.obj";
	std::string m_ModelName_Cube = "asset\\model\\particle_object_cube.obj";
	std::string m_ModelName_Sphere = "asset\\model\\particle_object_sphere.obj";
	std::string m_ModelName_Torii = "asset\\model\\torii\\torii_broken_";
	std::string m_Obj = ".obj";

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

	//	完全ランダムな色
	void SetParticle_Preset1();
	void SetParticle_Preset1(const D3DXVECTOR3& position);

	//	青～青緑
	void SetParticle_Preset2(const D3DXVECTOR3& position);

	//	全部白
	//	下から↑に小さくなっていく
	void SetParticle_Preset3(const float& area);

	void SetParticle_ToriiBloken_Rising();

	//	SetParticles 群---------------------------------------
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

	void SetParticle(const PARTICLE& par);
};

