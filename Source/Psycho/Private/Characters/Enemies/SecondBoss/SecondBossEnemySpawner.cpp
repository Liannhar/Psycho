

#include "Characters/Enemies/SecondBoss/SecondBossEnemySpawner.h"

#include "SecondBossEnemy.h"

void ASecondBossEnemySpawner::ActionWithEnemy(ABaseEnemy*& Enemy)
{
	Super::ActionWithEnemy(Enemy);

	if(const auto SecondBoss = Cast<ASecondBossEnemy>(Enemy))
	{
		SecondBoss->SetSwitchLightActors(SwitchLightsActors);
		SecondBoss->SetPointsLightsOnLevel(PointsLightsOnLevel);
		SecondBoss->SetBaseEnemiesSpawners(EnemiesSpawners);
		SecondBoss->StartBoss();
	}
	
}
