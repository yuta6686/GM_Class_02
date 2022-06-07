#pragma once
#include "gameObject.h"
class Ao_Sphere :
    public GameObject
{
private:
    Model* m_Model;

    ID3D11VertexShader* m_VertexShader = NULL;
    ID3D11PixelShader* m_PixelShader = NULL;
    ID3D11InputLayout* m_VertexLayout = NULL;
public:


    // GameObject を介して継承されました
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

};

