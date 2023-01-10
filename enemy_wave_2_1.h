#pragma once
#include "enemy_wave.h"
#include "enemy_wave_2_2.h"
class EnemyWave_2_1 :
    public EnemyWave
{
public:

    EnemyWave_2_1(const std::string& filename)
        :EnemyWave(filename, EW_2_1) {}



    virtual EnemyWave* CreateNextWave() override
    {
        return new EnemyWave_2_2("asset\\file\\EnemyGenerate2-2.txt");
    }
};

