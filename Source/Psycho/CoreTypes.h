#pragma once
#include "CoreTypes.generated.h"
//Типы атак
UENUM(BlueprintType)
enum EComboInput
{
	None,
	LightAttack,
	HeavyAttack
};

//AnimMontage и нужна ли была предыдущей атаке особое попадание
USTRUCT(BlueprintType)
struct FBlueprintMontageAttack
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EComboInput> TypeAttack;
	UPROPERTY(EditAnywhere)
	UAnimMontage* AttackMontage;
	UPROPERTY(EditAnywhere)
	bool PreviosAttackNeedTiming;
	
};
//Структура из массива типа атак и Анимации атаки
USTRUCT(BlueprintType)
struct FCombination
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FName Name;
	
	UPROPERTY(EditAnywhere)
	TArray<FBlueprintMontageAttack> Attack;
	
};