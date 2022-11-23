#pragma once
/** ---------------------------------------------------------
 *  [co_ui_default.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2022/8/16
 * ------------------------summary--------------------------
 * @brief  �X�v���C�g�`���ėp�I�ɍs��
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
    // todo UI_Information�|�C���^�ɂ��āA�C���N���[�h�Ȃ���
    bool SetUIInfo(UI_Information inf, D3DXVECTOR3 pos);

    bool ChangeWidthHeight(const D3DXVECTOR3& wh);

    bool ChangeDeployIndex(const int& deploy);

    bool LoadTexture(std::string fname);
};

