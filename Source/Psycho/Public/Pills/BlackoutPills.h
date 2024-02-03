// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pills/BasePills.h"
#include "BlackoutPills.generated.h"

UCLASS()
class PSYCHO_API UBlackoutPills : public UBasePills
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TArray<class ABaseEnemy*> DeactivatedEnemies;
	
public:
	void UsePill() override;
	void StopBlurring();
	void StopDamageDecrease();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect", meta = (ClampMin = "0.0"))
	float BlurringTime;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect", meta = (ClampMin = "0.0"))
	float BlurringStrength;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect", meta = (ClampMin = "0.0"))
	float DeactivateRadius;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect", meta = (ClampMax = "100"))
	uint8 DeactivatePercent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect", meta = (ClampMin = "0.0"))
	float DamageDecreaseTime;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect", meta = (ClampMin = "0.0"))
	float AttackDamageMultiplier;
};
