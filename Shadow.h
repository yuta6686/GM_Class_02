#pragma once
#include "gameObject.h"

//  Fieldを真似して作る
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


    // GameObject を介して継承されました
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

};

