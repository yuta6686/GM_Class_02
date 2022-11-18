#pragma once
#include "component.h"
#include "ResourceManager.h"
#include "texture.h"
class Polygon3DComponent :
    public Component
{
    ID3D11Buffer* m_VertexBuffer = NULL;
    std::shared_ptr<Resource> m_Texture;

    bool IsUseAlphaToCoverage = true;
    bool m_IsCullNone = false;
    bool m_IsChangeVertex = false;    
    bool m_IsVertical = true;
public:
    
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual void DrawImgui() override;

    void LoadTexture(std::string texture) {
        m_Texture = ResourceManger<Texture>::GetResource(texture);
    }

    void SetIsUseAlphaToCoverage(bool flag = true)
    {
        IsUseAlphaToCoverage = flag;
    }

    void SetIsCullNone(bool flag = true)
    {
        m_IsCullNone = flag;
    }

    void SetIsChangeVertex(bool flag = true) { m_IsChangeVertex = flag; }
    void SetIsVertical(bool flag) { m_IsVertical = flag; }

    void ChangeVertexDraw();
    void ChangeVertexDraw(const D3DXVECTOR4& color);
};

