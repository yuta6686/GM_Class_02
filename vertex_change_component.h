#pragma once
/** ---------------------------------------------------------
 *  VertexChangeComponent [vertex_change_component.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2022/11/21
 * ------------------------summary--------------------------
 * @brief  �e��UI�̒��_���ό`���邩�B
 ** ---------------------------------------------------------*/
 // ? ���̎����͔�������
//  ? UserInterfaceComponent�ɓ��ꂽ��ǂ��Ȃ��H
// todo ���Ƃ�UIC�Ɉڍs
#include "component.h"
class VertexChangeComponent :
    public Component
{
public:
    // Component ����Čp������܂���
    virtual void Init() override {};

    virtual void Uninit() override {};

    virtual void Update() override {};

    virtual void Draw() override {
        m_Parent->GetComponent<UserInterfaceComponent>()->ChangeVertexDraw();
    }

    virtual void DrawImgui() override {};

};

