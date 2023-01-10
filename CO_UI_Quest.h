#pragma once
/** ---------------------------------------------------------
 *  [CO_UI_Quest.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2022/8/9
 * ------------------------summary--------------------------
 * @brief   
 ** ---------------------------------------------------------*/
#include "component_object.h"

class CO_UI_Quest :
    public ComponentObject
{
private:
    float m_Divider;
    D3DXVECTOR3 m_WidthHeight;
    class UserInterfaceComponent* _uiComponent;
    class CountComponent* m_Count;
public:

    CO_UI_Quest();
    
    virtual void Init()override;

    virtual void Update()override;

    virtual void DrawImgui()override;

    void Start();
};

