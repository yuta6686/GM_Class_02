#pragma once
#include "enemy_wave.h"

class EnemyWave_3_3 :
    public EnemyWave
{
public:
    EnemyWave_3_3(const std::string& filename)
        :EnemyWave(filename, EW_3_3) {}

    virtual EnemyWave* CreateNextWave() override;

};

class EnemyWave_3_2 :
    public EnemyWave
{
public:
    EnemyWave_3_2(const std::string& filename)
        :EnemyWave(filename, EW_3_2) {}

    virtual EnemyWave* CreateNextWave() override
    {
        return new EnemyWave_3_3("asset\\file\\EnemyGenerate3-3.txt");
    }
};


class EnemyWave_3_1 :
    public EnemyWave
{
public:
    EnemyWave_3_1(const std::string& filename)
        :EnemyWave(filename, EW_3_1) {}

    virtual EnemyWave* CreateNextWave() override
    {
        return new EnemyWave_3_2("asset\\file\\EnemyGenerate3-2.txt");
    }
};


