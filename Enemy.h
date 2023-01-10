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

// https://yuta6686.atlassian.net/browse/AS-12 ステートマシンをエネミーの挙動に組み込む
class Enemy_StateMachine : public Enemy_Interface
{
public:
    Enemy_StateMachine() :Enemy_Interface(ENEMY_STATE_MACHINE) {}
    virtual void Init();
};

// EnemyStateMachieneを作る
class EnemyStateMachine : public StateMachine
{
public:

};

// EnemyStateを作る
