#pragma once
#pragma once
#include "enemy_wave.h"

class EnemyWave_2_3 :
    public EnemyWave
{
public:

    EnemyWave_2_3(const std::string& filename)
        :EnemyWave(filename, EW_2_3) {}

    virtual EnemyWave* CreateNextWave() override;

};

