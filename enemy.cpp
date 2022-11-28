#include "Enemy.h"
#include "random_velocity_component.h"
#include "random_jump_component.h"
#include "tracking_component.h"
#include "gravity_component.h"

void Enemy::Init()
{

    Enemy_Interface::Init();

    ModelDrawComponent* mdc = AddComponent< ModelDrawComponent>(COMLAYER_DRAW);
    mdc->SetSourcePath("asset\\model\\stone_white.obj");
    mdc->SetIsVariable(true);
    



    ComponentObject::Init();
}

void Enemy_Tracking::Init()
{

    Enemy_Interface::Init();
    ModelDrawComponent* mdc = AddComponent< ModelDrawComponent>(COMLAYER_DRAW);
    mdc->SetSourcePath("asset\\model\\stone_white.obj");
    mdc->SetIsVariable(true);

    AddComponent<TrackingComponent>(COMLAYER_SECOND);


    ComponentObject::Init();
}

void Enemy_Tracking_Fast::Init()
{

    Enemy_Interface::Init();

    ModelDrawComponent* mdc = AddComponent< ModelDrawComponent>(COMLAYER_DRAW);
    mdc->SetSourcePath("asset\\model\\stone_white.obj");
    mdc->SetIsVariable(true);

    AddComponent<TrackingComponent>(COMLAYER_SECOND)->SetSpeed(0.3f);


    ComponentObject::Init();
}

void Enemy_Tracking_Late::Init()
{

    Enemy_Interface::Init();

    ModelDrawComponent* mdc = AddComponent< ModelDrawComponent>(COMLAYER_DRAW);
    mdc->SetSourcePath("asset\\model\\stone_white.obj");

    mdc->SetIsVariable(true);

    AddComponent<TrackingComponent>(COMLAYER_SECOND)->SetSpeed(0.01f);



    ComponentObject::Init();
}

void Enemy_Move_Straight::Init()
{

    Enemy_Interface::Init();

    ModelDrawComponent* mdc = AddComponent< ModelDrawComponent>(COMLAYER_DRAW);
    mdc->SetSourcePath("asset\\model\\stone_white.obj");
    mdc->SetIsVariable(true);



    AddComponent<RandomVelocityComponent>(COMLAYER_SECOND)->SetSpeed(0.1f);


    ComponentObject::Init();
}

void Enemy_Jump::Init()
{

    Enemy_Interface::Init();

    ModelDrawComponent* mdc = AddComponent< ModelDrawComponent>(COMLAYER_DRAW);
    mdc->SetSourcePath("asset\\model\\stone_white.obj");
    mdc->SetIsVariable(true);

    AddComponent< GravityComponent>(COMLAYER_SECOND);

    AddComponent<RandomVelocityComponent>(COMLAYER_SECOND)->SetSpeed(0.1f);

    AddComponent< RandomJumpComponent>(COMLAYER_DRAW);

    ComponentObject::Init();
}

void Enemy_Boss::Init()
{

    Enemy_Interface::Init();

    ModelDrawComponent* mdc = AddComponent< ModelDrawComponent>(COMLAYER_DRAW);
    mdc->SetSourcePath("asset\\model\\enemy_boss.obj");
    mdc->SetIsVariable(true);


    AddComponent< GravityComponent>(COMLAYER_SECOND);

    AddComponent<RandomVelocityComponent>(COMLAYER_SECOND)->SetSpeed(0.5f);

    AddComponent< RandomJumpComponent>(COMLAYER_DRAW);

    ComponentObject::Init();

    m_Scale = { 2.0f,2.0f,2.0f };
}
