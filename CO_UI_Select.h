#pragma once
/** ---------------------------------------------------------
 *  [CO_UI_Select.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2022/8/16
 * ------------------------summary--------------------------
 * @brief  ExitÇ∑ÇÈÇ∆Ç´ÇÃUI
 * MessageBoxìIÇ»Ç‚Ç¬
 ** ---------------------------------------------------------*/
#include "component_object.h"

class CO_UI_Select :
    public ComponentObject
{
private:
//  inline static const ïœêî
    inline static const std::string m_FileName_Select_True = 
        "asset\\texture\\UI_Select_true.png";

    inline static const std::string m_FileName_Select_True_Blue = 
        "asset\\texture\\UI_Select_true_blue.png";

    inline static const std::string m_FileName_Select_False = 
        "asset\\texture\\UI_Select_false.png";

    inline static const std::string m_FileName_Select_False_Blue = 
        "asset\\texture\\UI_Select_false_blue.png";

    inline static const std::vector<std::string> m_FileNameBox
        = { 
        "asset\\texture\\UI_GiveUp.png" ,
        "asset\\texture\\UI_Continue.png" ,
        "asset\\texture\\UI_ReturnToTitle.png" 
    };
    

//  í èÌÉÅÉìÉoïœêî
    bool m_IsString = false;
    D3DXVECTOR3 m_TruePosition;
    D3DXVECTOR3 m_FalsePosition;
public:
    virtual void Init()override;

    static std::string GetFileName_SelectTrue() 
    { return m_FileName_Select_True; }

    static std::string GetFileName_SelectTrue_Blue() 
    { return m_FileName_Select_True_Blue; }

    static std::string GetFileName_SelectFalse() 
    { return m_FileName_Select_False; }

    static std::string GetFileName_SelectFalse_Blue() 
    { return m_FileName_Select_False_Blue; }

    static std::vector<std::string> GetFileName_Box() 
    { return m_FileNameBox; }

    void SetIsString(bool flag = true) { m_IsString = flag; }
    bool GetIsString()const { return m_IsString; }

    void SetTrue_False_Position(
        const D3DXVECTOR3& true_pos, const float& up);

    D3DXVECTOR3 GetTrue_False_Position(bool flag);

    void PositionAdaptation(bool flag);
};

