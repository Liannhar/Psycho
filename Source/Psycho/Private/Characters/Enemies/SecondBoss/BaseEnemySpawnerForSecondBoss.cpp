// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/SecondBoss/BaseEnemySpawnerForSecondBoss.h"

void ABaseEnemySpawnerForSecondBoss::ActionWithEnemy(ABaseEnemy*& Enemy)
{
	OnSpawn.Broadcast(Enemy);
}

