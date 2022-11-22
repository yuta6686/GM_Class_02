#pragma once
/** ---------------------------------------------------------
 *  HPComponent [hp_component.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2022/8/16
 * ------------------------summary--------------------------
 * @brief  プレイヤー・エネミーのHP
 ** ---------------------------------------------------------*/
#include "component.h"
#include "gameObject.h"

class HPComponent :
    public Component
{
private: // const
    inline static const float MERGINE = 50.0f;
    inline static const float LEFT_POSITION = MERGINE;
    inline static const float RIGHT_POSITION = 500.0f - MERGINE;
private:
    int m_Hp;    
    int m_MaxHp;    
    bool m_IsDeath;
    class UserInterfaceComponent* m_UIComponent;
public:
    HPComponent();
    
    virtual void Init() override;

    virtual void Uninit() override;

    virtual void Update() override;

    virtual void Draw() override;

    virtual void DrawImgui() override;

    void RecoverHp(const int& hp);
    void ResetHp();
    void SetMaxHp(const int& maxHp);
    void TakeDamage(const int& damage);

    // Getter
    float GetHpRatio() { return static_cast<float>(m_Hp) / static_cast<float>(m_MaxHp); }    
    int GetHp() { return m_Hp; }
    int GetMaxHp() { return m_MaxHp; }
    bool GetIsDeath()const { return m_IsDeath; }

    // static
    static float GetLEFTPOSITION() { return LEFT_POSITION; }
    static float GetRIGHTPOSITION() { return RIGHT_POSITION; }
};

