#pragma once
#include "component.h"
#include "gameObject.h"
#include "polygon3d_component.h"
#include "scene.h"
#include "manager.h"
#include "player.h"

//  �F��ς��邾���̋@�\��񋟂����OK
//  ������const�̐F���ABool�͂���Ȃ��B
class VertexChangerComponent_Color :
    public Component
{
protected:    
    D3DXVECTOR4 m_Color = { 1.0f,1.0f,1.0f,1.0f };   
public:    
    virtual void Init() override
    {

    }

    virtual void Uninit() override
    {
    }

    virtual void Update() override
    {      

    }

    virtual void Draw() override
    {
        m_Parent->GetComponent<Polygon3DComponent>()->ChangeVertexDraw(m_Color);
    }

    virtual void DrawImgui() override
    {
       
    }

    void SetColor(const D3DXVECTOR4& color)
    {
        m_Color = color;
    }

};

