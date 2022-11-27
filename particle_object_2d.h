#pragma once
#include "component_object.h"
#include "particle_object.h"
#include "texture.h"

#include "resource.h"
enum PARTICLE_TEXTURE_TYPE_2D
{    
    PARTICLE_TYPE_2D_RECT,
    PARTICLE_TYPE_2D_RECT_OUTLINE,    
    PARTICLE_TYPE_2D_TRIANGLE,
    PARTICLE_TYPE_2D_TRIANGLE_OUTLINE,
    PARTICLE_TYPE_2D_CIRCLE,
    PARTICLE_TYPE_2D_CIRCLE_OUTLINE,
    PARTICLE_TYPE_2D_MAX,
};
struct PARTICLE2D
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

    D3DXVECTOR4 col4 = { 1.0f,1.0f,1.0f,1.0f };

    D3DXVECTOR4 m_Color4OverLifeTime_Start = { 1.0f,1.0f,1.0f,1.0f };
    D3DXVECTOR4 m_Color4OverLifeTime_End = { 0.0f,0.0f,0.0f,0.0f };

    float m_SizeOverLifeTime_Start = 0.0f;
    float m_SizeOverLifeTime_End = 1.0f;
};
class ParticleObject_2D :
    public ComponentObject
{
private:
    inline static const int PARTICLE_MAX = 1000;
    inline static const std::vector<std::string> m_TextureName
        = {
        "asset\\texture\\particle_rect.png",
        "asset\\texture\\particle_rect_outline.png",
        "asset\\texture\\particle_triangle.png",
        "asset\\texture\\particle_triangle_outline.png",
        "asset\\texture\\particle_circle.png",
        "asset\\texture\\particle_circle_outline.png",            
    };

    std::vector<PARTICLE2D> m_Particles;

    std::vector<std::shared_ptr<Resource>>  m_Textures;

    std::shared_ptr <VertexShader> m_VertexShader;
    std::shared_ptr<PixelShader> m_PixelShader;

    VERTEX_3D m_vertex[4];
    ID3D11Buffer* m_VertexBuffer = NULL;

    Camera* m_Camera;

    D3DXVECTOR3 m_WidthHeight = { 100.0f,100.0f,0.0f };
public:
    static std::string GetTextureName(const int& index)
    {
        return m_TextureName[index];
    }

    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual void DrawImgui()override;

    void SetParticle_Rising();
    void SetParticle_Descent(const D3DXVECTOR4& end_color);

    void SetParticle_Gather(const D3DXVECTOR4& end_color);
    void SetParticle_Explosion(const D3DXVECTOR3& pos);

    void SetParticles(const PARTICLE2D& particle);
};

