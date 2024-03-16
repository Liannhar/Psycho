// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerBoxes/FirstBossStartFightTriggerBox.h"

#include "EnemySpawner.h"
#include "FirstBossEnemy.h"
#include "FirstBossEnemySpawner.h"
#include "FirstBossStartFightActor.h"

void AFirstBossStartFightTriggerBox::Action()
{
	Super::Action();
	if(FirstBossSpawner)
	{
		FirstBossSpawner->SpawnOneEnemy();
		FirstBossEnemy = FirstBossSpawner->GetFirstBoss();
		if(const auto StartFightFirstBossActor = Cast<AFirstBossStartFightActor>(StartFightActor); FirstBossEnemy && StartFightFirstBossActor)
		{
			StartFightFirstBossActor->AddStartEnemies(FirstBossEnemy);
			StartFightFirstBossActor->FirstBoss = FirstBossEnemy;
		}
	}
}
