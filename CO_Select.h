#pragma once
/** ---------------------------------------------------------
 *  [CO_Select.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2022/8/16
 * ------------------------summary--------------------------
 * @brief  リザルトシーンのUI部分
 ** ---------------------------------------------------------*/
#include "component_object.h"

enum SELECT_NEXT {
    SELECT_NO=-1,
    SELECT_GIVE_UP,
    SELECT_CONTINUE,
    SELECT_RETURN_TO_TITLE,
    SELECT_MAX
};
class CO_UI_Select;
class CO_Select :
    public ComponentObject
{
private:
    //  通常メンバ変数
    std::shared_ptr<Scene> _scene;

    std::vector<CO_UI_Select*> m_UISelects;
    std::vector<CO_UI_Select*> m_UISelects_String;
    std::vector<CO_UI_Select*> m_UISelects_Box;

    std::string m_NowFileName_true;
    std::string m_NowFileName_false;

    class Audio* m_SESelect;
    class Audio* m_SEKettei;

    int m_SelectIndex;
    int m_Select;

    bool m_IsBlue;

    D3DXVECTOR4 m_TrueColor;    
public:   
    // コンストラクタ
    CO_Select();

    virtual void Init()override;  
    virtual void Update()override;

    int GetSelect()const { return m_Select; }
    void SetBlue(bool flag = true);
    void SetColor(const D3DXVECTOR4& col) { m_TrueColor = col; }
};

