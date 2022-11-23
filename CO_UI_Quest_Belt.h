#pragma once
/** ---------------------------------------------------------
 *  [CO_UI_Quest_Belt.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2022/8/9
 * ------------------------summary--------------------------
 * @brief  チュートリアルの動くUI
 ** ---------------------------------------------------------*/
#include "component_object.h"

class CO_UI_Quest_Belt :
    public ComponentObject
{
private:
    float m_Divider;

    bool m_IsReverse;

    D3DXVECTOR3 m_WidthHeight;
    D3DXVECTOR3 m_Departure;
    D3DXVECTOR3 m_Destination;

    class UserInterfaceComponent* m_UIComponent;
    class CountComponent* m_Count;    
public:
    CO_UI_Quest_Belt();

    virtual void Init()override;
    virtual void Update()override;
    virtual void DrawImgui()override;

    void Start(const bool& in,
        const int& max,
        const int& delay,
        bool reverse = false);

    void SetDestination(const D3DXVECTOR3& dest) { m_Destination = dest; }
    void SetDeparture(const D3DXVECTOR3& dep) { m_Departure = dep; }
};

