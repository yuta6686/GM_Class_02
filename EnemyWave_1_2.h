#pragma once
#include "EnemyWave.h"
#include "EnemyWave_1_3.h"
class EnemyWave_1_2 :
    public EnemyWave
{
public:

    EnemyWave_1_2(const std::string& filename)
        :EnemyWave(filename) {}

    EnemyWave_1_2(const std::string& filename, const bool& isTracking)
        :EnemyWave(filename, isTracking) {}

    virtual EnemyWave* CreateNextWave() override
    {
        return new EnemyWave_1_3("asset\\file\\EnemyGenerate1-3.txt",true);
    }
};

