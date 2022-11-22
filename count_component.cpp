#include "count_component.h"

CountComponent::CountComponent()
    : _count(0),
    m_CountOffset(0),
    m_MaxCount(60),
    m_Delay(0),
    m_0to1(0.0f),
    m_In(false),
    m_Finish(false),
    m_InFinish(false)
{
}

void CountComponent::Init() { _count = 0; }

void CountComponent::Uninit() { }

void CountComponent::Update()
{
    if (m_In) {
        if (_count + m_Delay > 0)
        {
            _count--;
        }
        else
        {
            m_InFinish = true;
        }


        m_0to1 = static_cast<float>(min(_count + m_Delay, m_MaxCount)) / static_cast<float>(m_MaxCount);
    }
    else
    {
        //  Å‘å’l‚ÉŽŠ‚Á‚½ --> m_Count >= m_Delay + m_MaxCount
        if (_count - m_Delay > m_MaxCount)
        {
            m_Finish = true;
        }
        else
        {
            _count++;
        }


        m_0to1 = static_cast<float>(max(_count - m_Delay, 0)) / static_cast<float>(m_MaxCount);
    }
}

void CountComponent::Draw() { }

void CountComponent::DrawImgui() {  }

void CountComponent::Start(bool in,
    const int& max,
    const int& delay,
    const int& offset) 
{
    m_CountOffset = offset;
    m_MaxCount = max;
    m_Delay = delay;


    m_InFinish = false;
    m_Finish = false;
    m_In = in;


    if (m_In) {
        _count = m_MaxCount + m_Delay - m_CountOffset;
    }
    else
    {
        _count = m_CountOffset;
    }
}