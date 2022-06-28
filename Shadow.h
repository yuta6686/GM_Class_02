#pragma once
#include "gameObject.h"

//  Field‚ğ^—‚µ‚Äì‚é
class Shadow :
    public GameObject
{
private:
    float m_pos;

    ID3D11Buffer* m_VertexBuffer = NULL;
    std::shared_ptr<Texture> m_Texture;

    std::shared_ptr <VertexShader> m_VertexShader;
    std::shared_ptr<PixelShader> m_PixelShader;

    void InitVertex(VERTEX_3D* vertex);
public:


    // GameObject ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

};

