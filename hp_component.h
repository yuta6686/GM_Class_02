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
    int _hp;    
    int _maxHp;    
    bool _isDeath;
    class UserInterfaceComponent* _uiComponent;
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
    float GetHpRatio() { return static_cast<float>(_hp) / static_cast<float>(_maxHp); }
    int GetHp() { return _hp; }
    int GetMaxHp() { return _maxHp; }
    bool GetIsDeath()const { return _isDeath; }

    // static
    static float GetLEFTPOSITION() { return LEFT_POSITION; }
    static float GetRIGHTPOSITION() { return RIGHT_POSITION; }
};

