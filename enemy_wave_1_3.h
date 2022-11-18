#pragma once
#include "enemy_wave.h"
#include "manager.h"


class EnemyWave_1_3 :
    public EnemyWave
{
public:

    EnemyWave_1_3(const std::string& filename)
        :EnemyWave(filename, EW_1_3) {}


    virtual EnemyWave* CreateNextWave() override;
};