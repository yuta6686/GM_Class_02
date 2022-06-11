#pragma once
#include "gameObject.h"
#include "model.h"
class stage_corridor :
    public GameObject
{
private:
    std::shared_ptr<Model> m_Model;

    std::shared_ptr <VertexShader> m_VertexShader;
    std::shared_ptr<PixelShader> m_PixelShader;

public:

    // GameObject を介して継承されました
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

};

