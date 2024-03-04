// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/FirstBoss/FirstBossEnemySpawner.h"

#include "FirstBossEnemy.h"

void AFirstBossEnemySpawner::ActionWithEnemy(ABaseEnemy* Enemy)
{
	Super::ActionWithEnemy(Enemy);
	if(const auto Boss = Cast<AFirstBossEnemy>(Enemy))
	{
		Boss->SetThatNeedBossKey(DoorThatNeedBossKey);
	}
}
