#pragma once
#include "gameObject.h"
class UserInterface :
    public GameObject
{
protected:
    ID3D11Buffer* m_VertexBuffer = NULL;
    std::shared_ptr<Resource> m_Texture;

    std::shared_ptr<VertexShader> m_VertexShader;
    std::shared_ptr<PixelShader> m_PixelShader;

    D3DXVECTOR3 m_mainPos;
    float m_Radius;
    VERTEX_3D m_vertex[4];
    D3DXVECTOR3 m_Offset = { SCREEN_WIDTH / 2.0f,SCREEN_HEIGHT / 2.0f,0.0f };
public:    
    virtual void Init() override;
    virtual void Uninit() override;
    virtual void Update() override;
    virtual void Draw() override;
};

