#pragma once
#include "main.h"
#include "Resource.h"
#include "Enemy_Interface.h"
#include "StageLimitComponent_Reflect.h"
#include "RandomVelocityComponent.h"
#include "RandomJumpComponent.h"

class Enemy : public Enemy_Interface
{
public:
    Enemy() :Enemy_Interface(ENEMY_NORMAL){}

    virtual void Init() {
        
        Enemy_Interface::Init();

        ModelDrawComponent* mdc = AddComponent< ModelDrawComponent>(COMLAYER_DRAW);
        mdc->SetSourcePath("asset\\model\\stone_white.obj");
        mdc->SetIsVariable(true);        


        ComponentObject::Init();
    }
};

class Enemy_Tracking : public Enemy_Interface
{
public:
    Enemy_Tracking() :Enemy_Interface(ENEMY_TRACKING) {}

    virtual void Init() {

        Enemy_Interface::Init();
        ModelDrawComponent* mdc = AddComponent< ModelDrawComponent>(COMLAYER_DRAW);
        mdc->SetSourcePath("asset\\model\\stone_white.obj");
        mdc->SetIsVariable(true);        

        AddComponent<TrackingComponent>(COMLAYER_SECOND);


        ComponentObject::Init();
    }
};

class Enemy_Tracking_Fast : public Enemy_Interface
{
public:
    Enemy_Tracking_Fast() :Enemy_Interface(ENEMY_TRACKING_FAST) {}

    virtual void Init() {

        Enemy_Interface::Init();

        ModelDrawComponent* mdc = AddComponent< ModelDrawComponent>(COMLAYER_DRAW);
        mdc->SetSourcePath("asset\\model\\stone_white.obj");        
        mdc->SetIsVariable(true);

        AddComponent<TrackingComponent>(COMLAYER_SECOND)->SetSpeed(0.3f);


        ComponentObject::Init();
    }
};

class Enemy_Tracking_Late : public Enemy_Interface
{
public:
    Enemy_Tracking_Late() :Enemy_Interface(ENEMY_TRACKING_LATE) {}

    virtual void Init() {

        Enemy_Interface::Init();

        ModelDrawComponent* mdc = AddComponent< ModelDrawComponent>(COMLAYER_DRAW);
        mdc->SetSourcePath("asset\\model\\stone_white.obj");
        
        mdc->SetIsVariable(true);

        AddComponent<TrackingComponent>(COMLAYER_SECOND)->SetSpeed(0.01f);

        

        ComponentObject::Init();
    }
};

class Enemy_Move_Straight : public Enemy_Interface
{
public:
    Enemy_Move_Straight() :Enemy_Interface(ENEMY_MOVE_STRAIGHT) {}

    virtual void Init() {

        Enemy_Interface::Init();

        ModelDrawComponent* mdc = AddComponent< ModelDrawComponent>(COMLAYER_DRAW);
        mdc->SetSourcePath("asset\\model\\stone_white.obj");
        mdc->SetIsVariable(true);        


        
        AddComponent<RandomVelocityComponent>(COMLAYER_SECOND)->SetSpeed(0.1f);


        ComponentObject::Init();
    }
};

class Enemy_Jump :public Enemy_Interface
{
public:
    Enemy_Jump() :Enemy_Interface(ENEMY_JUMP) {}

    virtual void Init() {

        Enemy_Interface::Init();

        ModelDrawComponent* mdc = AddComponent< ModelDrawComponent>(COMLAYER_DRAW);
        mdc->SetSourcePath("asset\\model\\stone_white.obj");
        mdc->SetIsVariable(true);
        

        AddComponent<RandomVelocityComponent>(COMLAYER_SECOND)->SetSpeed(0.1f);

        AddComponent< RandomJumpComponent>(COMLAYER_DRAW);

        ComponentObject::Init();
    }
};