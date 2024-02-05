// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemies/BaseEnemy.h"
#include "FirstBossEnemy.generated.h"


UCLASS()
class PSYCHO_API AFirstBossEnemy : public ABaseEnemy
{
	GENERATED_BODY()
public:
	void StartEffectMoving();
	void EndEffectMoving();
protected:
	FTimerHandle EffectTImer;
	UPROPERTY(EditAnywhere,Category="Effect")
	float EffectTime = 1.5f;
};
