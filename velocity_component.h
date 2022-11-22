#pragma once
#include "component.h"
#include "gameObject.h"

class VelocityComponent :
    public Component
{
private: // const
    inline static const float LATE = 0.1f;
    inline static const float FAST = 1.0f;
private:
    class CountComponent* m_Counter;

    float m_Liner;
    bool m_IsSlow;
    bool m_IsBack;
    bool m_HasVelocityChanged;
    bool m_HasVelocityChanged_Y;
    bool m_NoLinerEffect;
    bool m_NoAdd;

    D3DXVECTOR3 m_PreviousVelocity;
    D3DXVECTOR3 m_OldPos;

public: // 変数    
    D3DXVECTOR3 m_Velocity = { 0.0f,0.0f,0.0f };
    
public:// 関数

    // コンストラクタ
    VelocityComponent();

    // Component を介して継承されました
    virtual void Init() override;
    virtual void Uninit() override;
    virtual void Update() override;
    virtual void Draw() override;
    virtual void DrawImgui() override;

    void SetIsSlow(bool flag = true) { m_IsSlow = flag; }
    void SetIsBack(bool flag = true) { m_IsBack = flag; }

    void SetStart(const bool& in, const int& max, const int& delay,const int& offset);
    void SetNoAdd(const bool& flag = true) { m_NoAdd = flag; }

    void SetOldPos(char xyz);
    void SetOldPos(char xyz, float ypos);       

    bool GetHasVelocityChanged()const { return m_HasVelocityChanged; }
    bool GetHasVelocityChanged_Y()const { return m_HasVelocityChanged_Y; }

    void SetNoLinerEffect(bool flag = true) { m_NoLinerEffect = flag; }

};

