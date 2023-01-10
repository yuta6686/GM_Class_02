#pragma once
/** ---------------------------------------------------------
 *  [vertex_changer_color_component.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2022/12/13
 * ------------------------summary--------------------------
 * @brief  �F��ς��邾���̋@�\���������R���|�[�l���g
 ** ---------------------------------------------------------*/
#include "component.h"
#include "gameObject.h"

class VertexChangerComponent_Color :
    public Component
{
protected:    
    D3DXVECTOR4 m_Color = { 1.0f,1.0f,1.0f,1.0f };   
public:    

    void SetColor(const D3DXVECTOR4& color) { m_Color = color; }

    // Component ����Čp������܂���
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual void DrawImgui() override;    
};

