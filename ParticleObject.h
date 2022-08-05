#pragma once
#include "gameObject.h"
#include "scene.h"
#include "manager.h"
#include "camera.h"
struct PARTICLE
{
	int		status;		// 状態
	D3DXVECTOR3	pos;		// 位置
	D3DXVECTOR3	vel;		// 速度
	D3DXVECTOR3	acc;		// 加速度
	float	size;		// 大きさ
	int		life;		// 消滅時間(フレーム数)

	D3DXCOLOR col;		// 色
};
class ParticleObject :
    public GameObject
{
private:
	inline static const int PARTICLE_MAX = 1000;
	std::vector<PARTICLE> m_Particles;

	std::shared_ptr<Texture> m_Texture;
	ID3D11Buffer* m_VertexBuffer = NULL;
	std::shared_ptr <VertexShader> m_VertexShader;
	std::shared_ptr<PixelShader> m_PixelShader;


	Camera* m_Camera;
public:    
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

};

