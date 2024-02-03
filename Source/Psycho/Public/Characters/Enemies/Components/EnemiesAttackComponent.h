// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Components/AttackComponent.h"
#include "EnemiesAttackComponent.generated.h"

/**
 * 
 */
UCLASS()
class PSYCHO_API UEnemiesAttackComponent : public UAttackComponent
{
	GENERATED_BODY()
public:
	virtual void StartComboAttack(EComboInput Input) override;
};
