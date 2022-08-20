#pragma once
#pragma once
#include "EnemyWave.h"

class EnemyWave_2_3 :
    public EnemyWave
{
public:

    EnemyWave_2_3(const std::string& filename)
        :EnemyWave(filename, EW_2_3) {}

    virtual EnemyWave* CreateNextWave() override;

};

