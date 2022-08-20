#include "EnemyWave_1_3.h"
#include "CO_EnemyWave.h"

EnemyWave* EnemyWave_1_3::CreateNextWave()
{
    std::shared_ptr<Scene> scene = Manager::GetScene();
    scene->GetGameObject<CO_EnemyWave>()->SetIsStageClear(true);
    return new EnemyWave_1_3("asset\\file\\EnemyGenerate1-3.txt");
};