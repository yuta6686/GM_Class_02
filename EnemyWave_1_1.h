#pragma once
#include "EnemyWave.h"
#include "EnemyWave_1_2.h"
class EnemyWave_1_1 :
    public EnemyWave
{
public:

    EnemyWave_1_1(const std::string& filename) 
        :EnemyWave(filename,EW_1_1){}



    virtual EnemyWave* CreateNextWave() override
    {
        return new EnemyWave_1_2("asset\\file\\EnemyGenerate1-2.txt");
    }
};

