#pragma once
#include "gameObject.h"
class TitlePolygon :
    public GameObject
{
private:
    D3DXVECTOR3 m_mainPos;
    D3DXVECTOR3 m_Offset = { SCREEN_WIDTH / 2.0f,SCREEN_HEIGHT / 2.0f,0.0f };

    ID3D11Buffer* m_VertexBuffer = NULL;
    //ID3D11ShaderResourceView*	m_Texture = NULL;
    std::shared_ptr<Resource> m_Texture;

    std::shared_ptr<VertexShader> m_VertexShader;
    std::shared_ptr<PixelShader> m_PixelShader;
public:


    // GameObject ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

};

