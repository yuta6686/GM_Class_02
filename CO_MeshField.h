#pragma once
#include "component_object.h"
#include "shader_component.h"
#include "ResourceManager.h"
#include "manager.h"

class CO_MeshField :
    public ComponentObject
{
private:
    inline static const int VertexNum_Virtical = 20;
    inline static const int VertexNum_Horizontal = 20;

    float mMoveSpeed = 0.01f;
    float mHeightPower = 4.0f;
    float mHeightMul = 4.0f;
    float mWidth = 4.0f;
    float mDepth = 4.0f;

    float m_FieldHeight[VertexNum_Horizontal +1][VertexNum_Virtical +1];

    std::shared_ptr<Scene> mpScene;

    ID3D11Buffer* m_VertexBuffer = NULL;
    ID3D11Buffer* m_IndexBuffer = NULL;
    ID3D11ShaderResourceView* m_Texture = NULL;
    ID3D11ShaderResourceView* m_Texture2 = NULL;
    ID3D11ShaderResourceView* m_NormalTexture = NULL;
    ID3D11ShaderResourceView* m_PixelNoiseTexture = NULL;

    VERTEX_3D m_Vertex[VertexNum_Horizontal + 1][VertexNum_Virtical +1];

    std::shared_ptr<VertexShader> m_VertexShader;
    std::shared_ptr<PixelShader> m_PixelShader;
    
    void SettingHash(unsigned int seed);
    unsigned int GetHash(int x, int y);
    float Fade(float t);
    float GetValue(int x, int y);
    float valueNoise(float x,float y);
    float Lerp(float a, float b, float t);
    float Grad(unsigned int hash, float a, float b);
    float PerlinNoise(float x, float y);
public:
    virtual void Init()override;
    virtual void Uninit()override;
    virtual void Update()override;
    virtual void Draw()override;
    virtual void DrawImgui()override;

    float GetHeight(const D3DXVECTOR3& Position);

    int GetBloeckNumX(const D3DXVECTOR3& Position);
    int GetBloeckNumZ(const D3DXVECTOR3& Position);

    void Remap(const int& seed);
    void Move();
};

