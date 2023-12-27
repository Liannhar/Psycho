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
	UAttackComponent* GetAttackComponent();
	void Attack();
	void ChangeCountCombo();
	void ChangeMaxSpeed(float NewSpeed) const;
	void BlockAttack();
	void GetDamage();
	virtual void BeginPlay() override;
	bool GetIsTakenDamage() const {return IsTakenDamage;}
private:
	bool IsTakenDamage = false;
	FTimerHandle TimerDamage;
	void TakingDamage();
	void DontTakeDamage();

	void EndWait();
	float TimeForWaitDamage=3.0f;
	int32 AttacksCount=0;
	FTimerHandle WaitNextAttemptAttack;
	
};
