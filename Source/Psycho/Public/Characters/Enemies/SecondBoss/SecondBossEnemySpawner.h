// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemies/EnemySpawner.h"
#include "SecondBossEnemySpawner.generated.h"

class ABaseEnemySpawnerForSecondBoss;
class APointLight;
class ASwitchLightActor;
/**
 * 
 */
UCLASS()
class PSYCHO_API ASecondBossEnemySpawner : public AEnemySpawner
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere,Category="SecondBoss")
	TArray<APointLight*> PointsLightsOnLevel;
	UPROPERTY(EditAnywhere,Category="SecondBoss")
	TArray<ASwitchLightActor*> SwitchLightsActors;
	UPROPERTY(EditAnywhere,Category="SecondBoss")
	TArray<ABaseEnemySpawnerForSecondBoss*> EnemiesSpawners;

	virtual void ActionWithEnemy(ABaseEnemy*& Enemy) override;
	
};
