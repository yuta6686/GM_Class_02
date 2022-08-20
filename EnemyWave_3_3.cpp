#include "EnemyWave_3_all.h"
#include "CO_EnemyWave.h"

EnemyWave* EnemyWave_3_3::CreateNextWave()
{
    std::shared_ptr<Scene> scene = Manager::GetScene();
    scene->GetGameObject<CO_EnemyWave>()->SetIsStageClear(true);
    return new EnemyWave_3_3("asset\\file\\EnemyGenerate3-3.txt");
}