#pragma once
/** ---------------------------------------------------------
 *  [CO_UI_Quest_Purpose.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2022/8/9
 * ------------------------summary--------------------------
 * @brief  チュートリアルのクエスト
 ** ---------------------------------------------------------*/
#include "component_object.h"

class CO_UI_Quest_Purpose :
    public ComponentObject
{
private:
    float m_Divider;
    D3DXVECTOR3 m_WidthHeight;
    class UserInterfaceComponent* _uiComponent;
    class CountComponent* m_Count;
public:
    CO_UI_Quest_Purpose();

    virtual void Init()override;
    virtual void Update()override;
    virtual void DrawImgui()override;

public:
    void Start();
    void SetTexture(std::string file);
};

