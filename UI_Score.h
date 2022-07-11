#pragma once
#include "UserInterface.h"
class UI_Score :
    public UserInterface
{
private:
    inline static const float MAIN_POS_X = 50.0f;
    inline static const float MAIN_POS_Y = 50.0f;

    inline static const int DIGIT_NUM = 4;

    float m_Count;
    static const int TEX_WIDHT_NUM = 10;
    static const int TEX_HEIGHT_NUM = 1;
    inline static const D3DXVECTOR3 m_cOffset = { 200.0f,0.0f ,0.0f};
    inline static const float X_MARGINE = -75.0f;
public:
    virtual void Init() override;
    virtual void Uninit() override;
    virtual void Update() override;
    virtual void Draw() override;

    void AddCount(const float& addcount) {
        if (addcount < 0.0f || addcount >= 1000000.0f)return;
        m_Count += addcount;
    }
};

