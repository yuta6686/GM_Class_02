#pragma once
#include "component.h"
#include "gameObject.h"

//  色を変えるだけの機能を提供すればOK
//  今あるconstの色情報、Boolはいらない。
class VertexChangerComponent_Color :
    public Component
{
protected:    
    D3DXVECTOR4 m_Color = { 1.0f,1.0f,1.0f,1.0f };   
public:    

    void SetColor(const D3DXVECTOR4& color) { m_Color = color; }

    // Component を介して継承されました
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual void DrawImgui() override;    
};

