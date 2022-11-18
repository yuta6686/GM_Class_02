#pragma once
#include "gameObject.h"
#include "component.h"
class TransformInit :
    public Component
{
private:
    D3DXVECTOR3 m_InitPosition = { 0.0f,0.0f,0.0f };
    D3DXVECTOR3 m_InitRotation = { 0.0f,0.0f,0.0f };
    D3DXVECTOR3 m_InitScale = { 1.0f,1.0f,1.0f };
public:
    // Component ‚ð‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
    virtual void Init() override 
    {
        m_Parent->SetPosition(m_InitPosition);
        m_Parent->SetRotation(m_InitRotation);
        m_Parent->SetScale(m_InitScale);
    };
    virtual void Uninit() override {};
    virtual void Update() override {};
    virtual void Draw() override {};
    virtual void DrawImgui()  override {};

    void SetInitPosition(const D3DXVECTOR3& pos) 
    {
        m_InitPosition = pos;
    }
    void SetInitRotation(const D3DXVECTOR3& rot)
    {
        m_InitRotation = rot;
    }
    void SetInitScale(const D3DXVECTOR3& scale) 
    {
        m_InitScale = scale;
    }

    void SetInitPosRot(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
    {
        m_InitPosition = pos;
        m_InitRotation = rot;
    }

    void SetInitPosScale(const D3DXVECTOR3& pos, const D3DXVECTOR3& scale)
    {
        m_InitPosition = pos;
        m_InitScale = scale;
    }

    void SetInitRotScale(const D3DXVECTOR3& rot, const D3DXVECTOR3& scale) {
        m_InitRotation = rot;
        m_InitScale = scale;
    }

    void SetInitTransform(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& scale)
    {
        m_InitPosition = pos;
        m_InitRotation = rot;
        m_InitScale = scale;
    }
};

