#pragma once
#include "ComponentObject.h"
class Cylinder :
    public ComponentObject
{
private:
    std::shared_ptr<Model> m_Model;

    std::shared_ptr <VertexShader> m_VertexShader;
    std::shared_ptr<PixelShader> m_PixelShader;
public:


    // GameObject ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual void DrawImgui() override;

};

