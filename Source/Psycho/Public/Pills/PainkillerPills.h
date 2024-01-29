// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pills/BasePills.h"
#include "PainkillerPills.generated.h"

/**
 * 
 */
UCLASS()
class PSYCHO_API UPainkillerPills : public UBasePills
{
	GENERATED_BODY()
private:
	FTimerHandle TimerPillEffect;

public:
	void UsePill() override;
	void EndInvulnerability();
	void EndAddiction();

	struct FTimerHandle& GetTimerHandler() { return TimerPillEffect; };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect")
	float InvulnerabilityTime;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect")
	float AddicitonTime;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect", meta = (ClampMin = "1.0"))
	float TakeDamageMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect", meta = (ClampMin = "0.0"))
	float SpeedMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effect", meta = (ClampMin = "0.0"))
	float AttackSpeedMultiplier;
};
