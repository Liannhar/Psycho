﻿#pragma once
#include "GameFramework/Actor.h"
#include "Templates/SubclassOf.h"
#include "CoreTypes.generated.h"

class ABaseWeapon;
class AEnemySpawner;

//Типы атак
UENUM(BlueprintType)
enum EComboInput
{
	None,
	LightAttack,
	HeavyAttack
};

//Стадии второго босса
UENUM(BlueprintType)
enum ESecondBossStages
{
	FirstStage,
	SecondStage,
	ThirdStage
};

/*
//Раунды боя 3 стадии
UENUM(BlueprintType)
enum ESecondBossRounds
{
	FirstRound,
	SecondRound,
	ThirdRound
};
*/

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
	UPROPERTY(EditAnywhere)
	float DamageDistance = 10.0f;
	
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

//Структура из полей сохранения игрока
USTRUCT(BlueprintType)
struct FPlayerSave
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,Category="Save Player")
	FVector PlayerLocation=FVector(0.0f,0.0f,0.0f);
	UPROPERTY(EditAnywhere,Category="Save Player")
	float CurrentPlayerHP=100.0f;
	UPROPERTY(EditAnywhere,Category="Save Player")
	float CurrentPlayerMaxHP=100.0f;
	UPROPERTY(EditAnywhere,Category="Save Player")
	TSubclassOf<ABaseWeapon> CurrentPlayerClassOfWeapon=nullptr;
	//Тут таблеточки будут)
	//UPROPERTY(EditAnywhere,Category="Save")
	//TArray<UBasePills*> Pills;
	
};

//Структура из полей сохранения игрока
USTRUCT(BlueprintType)
struct FCheckPointSave
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,Category="Save CheckPoint")
	FVector CheckPointLocation=FVector(0.0f,0.0f,0.0f);
	UPROPERTY(EditAnywhere,Category="Save CheckPoint")
	bool CheckPointNotUsed=false;
};

//Волны Спавнеров мобов
USTRUCT(BlueprintType)
struct FWaves
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere,Category="Enemy")
	TArray<AEnemySpawner*> EnemySpawners;
	UPROPERTY(EditAnywhere,Category="Enemy")
	int32 HowManyEnemiesCanBeInFront=0;
};

USTRUCT(BlueprintType)
struct FAttackAIMemory
{
	GENERATED_BODY()

	bool EnemyNotIsAttackingNow=true;
};

inline float CalculateDistanceBetweenActors(const AActor* Actor1, const AActor* Actor2)
{
	const FVector Location1 = Actor1->GetActorLocation();
	const FVector Location2 = Actor2->GetActorLocation();
	return FVector::Dist(Location1, Location2);
}

