// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pills/BasePills.h"
#include "FuryPills.generated.h"

/**
 * 
 */
UCLASS()
class PSYCHO_API UFuryPills : public UBasePills
{
	GENERATED_BODY()

private:
	FTimerHandle TimerTakeDamageTick;
public:
	void UsePill() override;
	void TakeDamage();
	void StopTakeDamage();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect")
	float TakeDamageTime;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect", meta = (ClampMin = "0", ClampMax = "100"))
	uint8 TakeDamagePercent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect", meta = (ClampMin = "0.1"))
	float TakeDamageTickTime;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect", meta = (ClampMin = "0.0"))
	float SpeedMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect", meta = (ClampMin = "0.0"))
	float AttackSpeedMultiplier;
};
