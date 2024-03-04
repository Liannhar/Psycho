// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemies/EnemySpawner.h"
#include "FirstBossEnemySpawner.generated.h"


class ADoorBaseActor;

UCLASS()
class PSYCHO_API AFirstBossEnemySpawner : public AEnemySpawner
{
	GENERATED_BODY()
protected:
	virtual void ActionWithEnemy(ABaseEnemy* Enemy) override;

	UPROPERTY(EditAnywhere,Category="Key")
	ADoorBaseActor* DoorThatNeedBossKey;
};
