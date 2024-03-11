// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemies/EnemySpawner.h"
#include "BaseEnemySpawnerForSecondBoss.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnSpawnEnemy,ABaseEnemy*);


/**
 * 
 */
UCLASS()
class PSYCHO_API ABaseEnemySpawnerForSecondBoss : public AEnemySpawner
{
	GENERATED_BODY()
protected:
	virtual void ActionWithEnemy(ABaseEnemy*& Enemy) override;
public:
	FOnSpawnEnemy OnSpawn;
};
