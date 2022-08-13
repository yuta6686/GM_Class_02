#pragma once
#include "EnemyWave.h"
#include "EnemyWave_2_3.h"
class EnemyWave_2_2 :
    public EnemyWave
{
public:

    EnemyWave_2_2(const std::string& filename)
        :EnemyWave(filename, EW_2_2) {}



    virtual EnemyWave* CreateNextWave() override
    {
        return new EnemyWave_2_3("asset\\file\\EnemyGenerate2-3.txt");
    }
};

