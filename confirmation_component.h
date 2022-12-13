#pragma once
/** ---------------------------------------------------------
 *  ConfirmationComponent [confirmation_component.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2022/8/8
 * ------------------------summary--------------------------
 * @brief  �m�F���b�Z�[�W�{�b�N�X��UI�ɏo���B
 *         IsYes()��Yes or No���擾
 ** ---------------------------------------------------------*/
#include "component.h"


class ConfirmationComponent :
    public Component
{
private:    
    class UserInterfaceComponent* _uiComponent;

    const std::string m_MessageBox =
        "asset\\texture\\message_box.dds";

    const std::string m_MessageBox_Yes = 
        "asset\\texture\\message_box_Yes.dds";

    const std::string m_MessageBox_No =
        "asset\\texture\\message_box_No.dds";

    bool m_IsYes = false;

    class Audio* m_SE;
    
public:   
    bool GetIsYes()const { return m_IsYes; }
    void SetIsYes(const bool& flag) { m_IsYes = flag; }


    // Component ����Čp������܂���
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual void DrawImgui() override;

};

