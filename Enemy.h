#pragma once
/** ---------------------------------------------------------
 *  [Enemy.h]
 *                                 @author: yanagisaya.yuta
 *                                 @date  : 2022/5/31
 * ------------------------summary--------------------------
 * @brief  
 ** ---------------------------------------------------------*/
#include "enemy_interface.h"
#include "state_machine.h"


class Enemy : public Enemy_Interface
{
public:
    Enemy() :Enemy_Interface(ENEMY_NORMAL){}

    virtual void Init();    


};

class Enemy_Tracking : public Enemy_Interface
{
public:
    Enemy_Tracking() :Enemy_Interface(ENEMY_TRACKING) {}

    virtual void Init();
};

class Enemy_Tracking_Fast : public Enemy_Interface
{
public:
    Enemy_Tracking_Fast() :Enemy_Interface(ENEMY_TRACKING_FAST) {}

    virtual void InitInternal();
};

class Enemy_Tracking_Late : public Enemy_Interface
{
public:
    Enemy_Tracking_Late() :Enemy_Interface(ENEMY_TRACKING_LATE) {}

    virtual void Init();
};

class Enemy_Move_Straight : public Enemy_Interface
{
public:
    Enemy_Move_Straight() :Enemy_Interface(ENEMY_MOVE_STRAIGHT) {}

    virtual void Init();
};

class Enemy_Jump :public Enemy_Interface
{
public:
    Enemy_Jump() :Enemy_Interface(ENEMY_JUMP) {}

    virtual void Init();
};

class Enemy_Boss :public Enemy_Interface
{
public:
    Enemy_Boss() :Enemy_Interface(ENEMY_BOSS) {}

    virtual void Init();
};

// https://yuta6686.atlassian.net/browse/AS-12 �X�e�[�g�}�V�����G�l�~�[�̋����ɑg�ݍ���
class Enemy_Rush : public Enemy_Interface
{
public:
    Enemy_Rush() :Enemy_Interface(ENEMY_STATE_MACHINE) {}
    virtual void Init();
};

// EnemyStateMachiene�����
class EnemyStateMachine_Component : public StateMachine
{
public:
    // StateMachine ����Čp������܂���
    virtual void InitInternal() override;
    virtual void DrawImgui()override;
};

// EnemyState�����
// State�Ƃ��ăG�l�~�[�̑ҋ@��Ԃ̎���
// https://yuta6686.atlassian.net/browse/AS-16
// -------------------------------------------
class EnemyStateIdle : public State
{
    inline static const std::string NAME = "Idle";
    inline static const int IDLE_TIME = 60;
    int _time;
public:
    EnemyStateIdle() :State(NAME),_time(0) {}
    virtual void Update() override;
};

// State�Ƃ��ăG�l�~�[�̐ڋߏ�Ԃ̎���
// https://yuta6686.atlassian.net/browse/AS-17 
// -------------------------------------------
class EnemyStateApproach : public State
{
private: // const
    inline static const std::string NAME = "Approach";

    // �U���ɑJ�ڂ��鋗��
    inline static const float APPROACH_DISTANCE = 10.0f;
private:
    // �v���C���[�̃|�C���^��������
    class Player* _player;

public:
    EnemyStateApproach() :State(NAME) {}
    virtual void Init()override;
    virtual void Update() override;    
    virtual void DrawImgui()override;
};

// State�Ƃ��ăG�l�~�[�̍U���̎���
// https://yuta6686.atlassian.net/browse/AS-14
// -------------------------------------------
class EnemyStateRush : public State
{
    inline static const std::string NAME = "Rush";

    D3DXVECTOR3 _vec;
public:
    
    EnemyStateRush(const D3DXVECTOR3& vec) :State(NAME),_vec(vec) {}
    virtual void Update() override;
};

