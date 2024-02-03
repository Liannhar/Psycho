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
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Collision", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* EnemyChannelCollision;
public:
	ABaseEnemy();
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="AI")
	UBehaviorTree* BehaviorTreeAsset;
	
	void EndEnemyAttack();
	void Attack();
	
	bool GetNotIsAttackingNow() const {return NotIsAttackingNow;}
	bool GetIsTakenDamage() const {return IsTakenDamage;}
	bool GetLastAttackIsHeavy() const;

	void ChangeCountCombo(int32 NewCombo,int32 NewCount,bool NeedRandomCount=false);
	void ChangeMaxSpeed(float NewSpeed) const;
	void BlockAttack();

	void Deactivate();
	void Reactivate();

	virtual void BeginPlay() override;

	void SetStartAttack();

	float GetBaseSpeed() const {return BaseSpeed;}
protected:
	UPROPERTY()
	bool IsTakenDamage = false;
	UPROPERTY()
	FTimerHandle TimerDamage;

	void TakingDamage();
	void DontTakeDamage();

	UPROPERTY()
	AController* OwnController;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Speed")
	float BaseSpeed = 400.0f;
	
	void EndWait();
	UPROPERTY()
	float TimeForWaitDamage=2.0f;
	UPROPERTY()
	int32 AttacksCount=0;
	UPROPERTY()
	int32 ComboIndex = 0;
	UPROPERTY()
	FTimerHandle WaitNextAttemptAttack;
	UPROPERTY()
	bool NotIsAttackingNow=true;
	
	virtual void Death() override;
};
