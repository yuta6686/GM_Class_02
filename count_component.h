#pragma once
/** ---------------------------------------------------------
 *  CountComponent [count_component.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2022/11/22
 * ------------------------summary--------------------------
 * @brief  
 ** ---------------------------------------------------------*/
#include "component.h"
#include "gameObject.h"
class CountComponent :
    public Component
{
private:
    static const int DEFAULT_MAX_COUNT = 60;
private:
    int _count;
    int m_CountOffset;
    int m_MaxCount;
    int m_Delay;

    float m_0to1;

    bool m_In;    
    bool m_Finish;
    bool m_InFinish;
public:    
    CountComponent();

    /** Start
     * @brief �v���J�n
     * @param "in"      true--> 0����X�^�[�g.false --> 1����X�^�[�g(to 0)
     * @param "max"     �v�����鎞�Ԃ̎w��
     * @param "delay"   �x��
     * @param "offset" �@
     */
    void Start(bool in,
        const int& max = DEFAULT_MAX_COUNT,
        const int& delay = 0,
        const int& offset = 0);

//  Getter--------------------------------------------------------------------    
    int GetCount()const { return max(_count - m_Delay, 0); }
    float Get0to1Count()const { return m_0to1; }
    bool GetStart()const { return m_In; }
    bool GetFinish()const { return m_Finish; }
    bool GetInFinist()const { return m_InFinish; }

    // Component ����Čp������܂���
    virtual void Init() override;
    virtual void Uninit() override;
    virtual void Update() override;
    virtual void Draw() override;
    virtual void DrawImgui() override;
};

