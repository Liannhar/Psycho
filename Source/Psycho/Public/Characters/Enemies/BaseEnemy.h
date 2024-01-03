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
	
	void EndEnemyAttack();
	void Attack();
	
	bool GetNotIsAttackingNow() const {return NotIsAttackingNow;}
	bool GetIsTakenDamage() const {return IsTakenDamage;}
	bool GetLastAttackIsHeavy() const;

	void ChangeCountCombo();
	void ChangeMaxSpeed(float NewSpeed) const;
	void BlockAttack();

	virtual void BeginPlay() override;

protected:
	bool IsTakenDamage = false;
	FTimerHandle TimerDamage;
	void TakingDamage();
	void DontTakeDamage();
	
	
	void EndWait();
	float TimeForWaitDamage=3.0f;
	int32 AttacksCount=0;
	FTimerHandle WaitNextAttemptAttack;

	bool NotIsAttackingNow=true;

	UAttackComponent* GetAttackComponent() const;
	UHealthComponent* GetHealthComponent() const;
	
};
