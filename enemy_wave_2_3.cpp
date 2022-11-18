#include "enemy_wave_2_3.h"
#include "co_enemy_wave.h"

EnemyWave* EnemyWave_2_3::CreateNextWave()
{
    std::shared_ptr<Scene> scene = Manager::GetScene();
    scene->GetGameObject<CO_EnemyWave>()->SetIsStageClear(true);
    return new EnemyWave_2_3("asset\\file\\EnemyGenerate2-3.txt");
}