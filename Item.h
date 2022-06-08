#pragma once
#include "main.h"
#include "model.h"
#include "gameObject.h"
class item :
    public GameObject
{

private:
    static inline std::shared_ptr<Model> m_Model;

    ID3D11VertexShader* m_VertexShader;
    ID3D11PixelShader* m_PixelShader;
    ID3D11InputLayout* m_VertexLayout;

public:
    virtual void Init() override;
    virtual void Uninit() override;
    virtual void Update() override;
    virtual void Draw() override;
};

