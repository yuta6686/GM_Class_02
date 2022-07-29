#pragma once
#include "UserInterface.h"
class UserInterface_Animation :
    public UserInterface
{

private:
    inline static const float MAIN_POS_X = 50.0f;
    inline static const float MAIN_POS_Y = 50.0f;

    inline static const int DIGIT_NUM = 4;

    static const int TEX_WIDHT_NUM = 10;
    static const int TEX_HEIGHT_NUM = 1;
    inline static const D3DXVECTOR3 OFFSET = { 200.0f,0.0f ,0.0f };    

    int m_Count;

public:
    virtual void Init() override;
    virtual void Uninit() override;
    virtual void Update() override;
    virtual void Draw() override;

    void AddCount(const int& addcount) {
        if (addcount < 0.0f || addcount >= 1000000.0f)return;
        m_Count += addcount;
    }
};

