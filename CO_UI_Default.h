#pragma once
/** ---------------------------------------------------------
 *  [co_ui_default.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2022/8/16
 * ------------------------summary--------------------------
 * @brief  スプライト描画を汎用的に行う
 ** ---------------------------------------------------------*/
#include "component_object.h"
#include "user_interface_component.h"

class CO_UI_Default :
    public ComponentObject
{
private:    
    UserInterfaceComponent* m_UIComponent;
public:
    virtual void Init()override;    

public:
    // todo UI_Informationポインタにして、インクルードなくす
    bool SetUIInfo(UI_Information inf, D3DXVECTOR3 pos);

    bool ChangeWidthHeight(const D3DXVECTOR3& wh);

    bool ChangeDeployIndex(const int& deploy);

    bool LoadTexture(std::string fname);
};

