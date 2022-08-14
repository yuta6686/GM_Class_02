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
	int		status;		// 状態
	int		type;
	D3DXVECTOR3	pos;		// 位置
	D3DXVECTOR3	vel;		// 速度
	D3DXVECTOR3	acc;		// 加速度
	D3DXVECTOR3 rot;	//	回転	
	D3DXVECTOR3 rot_vel;
	float	size;		// 大きさ
	int		life;		// 消滅時間(フレーム数)
	bool    use;	

	D3DXCOLOR col;		// 色

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

	//	完全ランダムな色
	void SetParticle_Preset1();	
	void SetParticle_Preset1(const D3DXVECTOR3& position);

	//	青～青緑
	void SetParticle_Preset2(const D3DXVECTOR3& position);

	//	全部白
	//	下から↑に小さくなっていく
	void SetParticle_Preset3(const float& area);

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

};

