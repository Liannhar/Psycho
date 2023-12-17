// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "BaseEnemy.generated.h"

class UBehaviorTree;
/**
 * 
 */
UCLASS()
class PSYCHO_API ABaseEnemy : public ABaseCharacter
{
	GENERATED_BODY()
public:
	ABaseEnemy();
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="AI")
	UBehaviorTree* BehaviorTreeAsset;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	bool IsAttacking=false;
	bool IsEnemyAttacking();
	void Attack();
	void ChangeMaxSpeed(float NewSpeed);
	void BlockAttack();
	void GetDamage();
};
