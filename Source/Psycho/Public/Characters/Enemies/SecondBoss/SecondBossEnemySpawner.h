// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemies/EnemySpawner.h"
#include "SecondBossEnemySpawner.generated.h"

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
	UPROPERTY(EditAnywhere,Category="Lights")
	TArray<APointLight*> PointsLightsOnLevel;
	UPROPERTY(EditAnywhere,Category="Lights")
	TArray<ASwitchLightActor*> SwitchLightsActors;

	virtual void ActionWithEnemy(ABaseEnemy*& Enemy) override;
	
};
