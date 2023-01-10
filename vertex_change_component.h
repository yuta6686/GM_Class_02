#pragma once
/** ---------------------------------------------------------
 *  VertexChangeComponent [vertex_change_component.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2022/11/21
 * ------------------------summary--------------------------
 * @brief  親のUIの頂点が変形するか。
 ** ---------------------------------------------------------*/
 // ? この実装は微妙かも
//  ? UserInterfaceComponentに入れたら良くない？
// todo あとでUICに移行
#include "component.h"
class VertexChangeComponent :
    public Component
{
public:
    // Component を介して継承されました
    virtual void Init() override {};

    virtual void Uninit() override {};

    virtual void Update() override {};

    virtual void Draw() override {
        m_Parent->GetComponent<UserInterfaceComponent>()->ChangeVertexDraw();
    }

    virtual void DrawImgui() override {};

};

