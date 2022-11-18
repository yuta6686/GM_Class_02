#pragma once
#include "gameObject.h"
#include "ComponentObject.h"
class RenderingTexture :
    public ComponentObject
{
private:
    VERTEX_3D m_vertex[4];
    ID3D11Buffer* m_VertexBuffer = NULL;

    inline static const D3DXVECTOR3 _screenHalf =
    { SCREEN_WIDTH / 2.0f,SCREEN_HEIGHT / 2.0f,0.0f };

    inline static const D3DXVECTOR3 m_mainPos = _screenHalf;
    inline static const D3DXVECTOR4 m_Color = { 1.0f,1.0f,1.0f,1.0f };

    
    

public:
    // GameObject ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

};

