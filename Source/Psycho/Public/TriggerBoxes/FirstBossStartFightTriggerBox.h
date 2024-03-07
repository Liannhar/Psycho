// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TriggerBoxes/CanStartFightTriggerBox.h"
#include "FirstBossStartFightTriggerBox.generated.h"

class AFirstBossEnemy;
class AFirstBossEnemySpawner;
/**
 * 
 */
UCLASS()
class PSYCHO_API AFirstBossStartFightTriggerBox : public ACanStartFightTriggerBox
{
	GENERATED_BODY()
public:
protected:
	virtual void Action() override;

	UPROPERTY(EditAnywhere,Category="Trigger")
	AFirstBossEnemySpawner* FirstBossSpawner;

	UPROPERTY()
	AFirstBossEnemy* FirstBossEnemy;

	FTimerHandle WaitTimerHandle;
};
