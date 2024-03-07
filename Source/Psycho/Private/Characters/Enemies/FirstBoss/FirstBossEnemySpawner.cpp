// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/FirstBoss/FirstBossEnemySpawner.h"

#include "FirstBossEnemy.h"

void AFirstBossEnemySpawner::ActionWithEnemy(ABaseEnemy*& Enemy)
{
	Super::ActionWithEnemy(Enemy);
	FirstBoss = Cast<AFirstBossEnemy>(Enemy);
	if(FirstBoss)
	{
		FirstBoss->SetThatNeedBossKey(DoorThatNeedBossKey);
	}
}
