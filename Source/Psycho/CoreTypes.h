#pragma once
#include "CoreTypes.generated.h"

UENUM(BlueprintType)
enum EComboInput
{
	None,
	LightAttack,
	HeavyAttack
};

USTRUCT(BlueprintType)
struct FBlueprintMontageAttack
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	UAnimMontage* AttackMontage;
	UPROPERTY(EditAnywhere)
	bool PreviosAttackNeedTiming;
	
};

USTRUCT(BlueprintType)
struct FCombination
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FName Name;
	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EComboInput>> TypeAttack;
	UPROPERTY(EditAnywhere)
	TArray<FBlueprintMontageAttack> Attack;
	
};