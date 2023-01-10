#pragma once
/** ---------------------------------------------------------
 *  ConfirmationComponent [confirmation_component.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2022/8/8
 * ------------------------summary--------------------------
 * @brief  確認メッセージボックスをUIに出す。
 *         IsYes()でYes or Noを取得
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


    // Component を介して継承されました
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual void DrawImgui() override;

};

