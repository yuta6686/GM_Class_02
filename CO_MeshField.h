#pragma once
#include "ComponentObject.h"
#include "TextureComponent.h"
#include "ShaderComponent.h"
#include "ResourceManager.h"
#include "manager.h"

class CO_MeshField :
    public ComponentObject
{
private:
    inline static const int VertexNum_Virtical = 30;
    inline static const int VertexNum_Horizontal = 30;

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

    float GetHeight(D3DXVECTOR3 Position);

    void Remap(const int& seed);
    void Move();
};

