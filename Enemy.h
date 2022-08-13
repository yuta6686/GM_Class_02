#pragma once
#include "main.h"
#include "Resource.h"
#include "Enemy_Interface.h"


class Enemy : public Enemy_Interface
{
public:
    Enemy() :Enemy_Interface(ENEMY_NORMAL){}

    virtual void Init() {
        
        Enemy_Interface::Init();

        ModelDrawComponent* mdc =
            new ModelDrawComponent("asset\\model\\stone_white.obj");

        AddComponent(mdc, COMLAYER_DRAW);

        

        ComponentObject::Init();
    }
};

class Enemy_Tracking : public Enemy_Interface
{
public:
    Enemy_Tracking() :Enemy_Interface(ENEMY_TRACKING) {}

    virtual void Init() {

        Enemy_Interface::Init();

        ModelDrawComponent* mdc =
            new ModelDrawComponent("asset\\model\\stone_white.obj");

        AddComponent(mdc, COMLAYER_DRAW);

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

        ModelDrawComponent* mdc =
            new ModelDrawComponent("asset\\model\\stone_white.obj");

        AddComponent(mdc, COMLAYER_DRAW);

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

        ModelDrawComponent* mdc =
            new ModelDrawComponent("asset\\model\\stone_white.obj");

        AddComponent(mdc, COMLAYER_DRAW);

        AddComponent<TrackingComponent>(COMLAYER_SECOND)->SetSpeed(0.01f);

        ComponentObject::Init();
    }
};