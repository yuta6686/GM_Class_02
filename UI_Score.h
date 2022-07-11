#pragma once
#include "UserInterface.h"
class UI_Score :
    public UserInterface
{
protected:
    inline static const float MAIN_POS_X = 50.0f;
    inline static const float MAIN_POS_Y = 50.0f;
       
    //  横枚数
    static const int TEX_WIDHT_NUM = 10;

    //  縦枚数
    static const int TEX_HEIGHT_NUM = 1;

    //  オフセット
    inline static const D3DXVECTOR3 m_cOffset = { 200.0f,0.0f ,0.0f};
        
    int m_Count;
public:
    virtual void Init() override;
    virtual void Uninit() override;
    virtual void Update() override;
    virtual void Draw() override;

    void AddCount(const int& addcount) {
        if (addcount < 0 || addcount >= 1000000)return;
        m_Count += addcount;
    }
};

