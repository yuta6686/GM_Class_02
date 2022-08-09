#pragma once
#include "Component.h"
#include "gameObject.h"
class CountComponent :
    public Component
{
private:
    int m_Count = 0;
    int m_MaxCount = 60;
    int m_Delay = 0;
    float m_0to1 = 0.0f;

    bool m_In = false;    
    bool m_Finish = false;
public:    
    virtual void Init() override
    {
        m_Count = 0;
    }
    virtual void Uninit() override {}
    virtual void Update() override
    {
        if (m_In) {
            if (m_Count + m_Delay > 0)
            {
                m_Count--;
            }     
            
        }        
        else
        {
            //  Å‘å’l‚ÉŽŠ‚Á‚½ --> m_Count >= m_Delay + m_MaxCount
            if (m_Count - m_Delay >= m_MaxCount)
            {
                m_Finish = true;
            }
            m_Count++;            
        }        

        m_0to1 = static_cast<float>(max(m_Count - m_Delay, 0)) / static_cast<float>(m_MaxCount);
    }
    virtual void Draw() override {}
    virtual void DrawImgui() override {}


    void SetParameter(        
        const int& max,
        const int& delay = 0)
    {        
        m_MaxCount = max;
        m_Delay = delay;
    }

    void Start(bool in)
    {        
        m_In = in;        
        m_Finish = false;

        if (m_In) {
            m_Count = m_MaxCount;
        }
        else
        {
            m_Count = 0;
        }
    }

    void Start(bool in,
        const int& max,
        const int& delay = 0) {        
        m_MaxCount = max;
        m_Delay = delay;        

        m_Finish = false;
        m_In = in;

        if (m_In) {
            m_Count = m_MaxCount;
        }
        else
        {
            m_Count = 0;
        }
    }

//  Getter--------------------------------------------------------------------    
    int GetCount()const { 
        return max(m_Count - m_Delay, 0); 
    }
    float Get0to1Count()const {        
        return m_0to1;
    }
    bool GetStart()const {
        return m_In;
    }
    bool GetFinish() { 
        return m_Finish; 
    }
};

