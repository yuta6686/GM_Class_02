#pragma once
#include "gameObject.h"
class Ao_Sphere :
    public GameObject
{
private:
    Model* m_Model=nullptr;

    ID3D11VertexShader* m_VertexShader = NULL;
    ID3D11PixelShader* m_PixelShader = NULL;
    ID3D11InputLayout* m_VertexLayout = NULL;
public:
    void LoadModel(std::string filename)
    {
        m_Model->Load(filename.c_str());
    }
    

    // GameObject ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

};

