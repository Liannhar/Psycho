// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "AttackDamageType.generated.h"

/**
 * 
 */
UCLASS()
class PSYCHO_API UAttackDamageType : public UDamageType
{
	GENERATED_BODY()
public:
	float DamageDistance=10.0f;
	int32 DamageDirection=0;
};
