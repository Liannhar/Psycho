// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemies/BaseEnemy.h"
#include "FirstBossEnemy.generated.h"


class ADoorBaseActor;
class AKeyActor;
class AFirstBossAIController;
class AFirstBossEffectActor;

UCLASS()
class PSYCHO_API AFirstBossEnemy : public ABaseEnemy
{
	GENERATED_BODY()
public:
	AFirstBossEnemy();
	void StartEffectMoving(int32 NewStaminaCost);
	void EndEffectMoving();
	
	bool ChangeStaminaCost(const int32& NewCost);
	void PreparationBossBeforeAttack(const EComboInput Type, const int32 NewCombo, const int32 NewCount, const bool NeedRandomCount,const int32 NewStaminaCost);
	void DeathConfigurations();

	virtual void Attack() override;

	int32 GetCurrentStamina() const {return CurrentStamina;}
	void SetThatNeedBossKey(ADoorBaseActor* NewDoor){DoorThatNeedBossKey = NewDoor;}
protected:
	FTimerHandle EffectTImer;
	UPROPERTY(EditAnywhere,Category="Effect")
	float EffectTime = 0.2f;
	
	int32 CurrentAttackStaminaCost = 0;
	UPROPERTY(BlueprintReadOnly)
	bool StaminaHaveRemainder = false;

	void MakeEffect();

	virtual void BeginPlay() override;

	UPROPERTY()
	AFirstBossAIController* AIController;

	FTimerHandle StaminaRecoverTimer;
	UPROPERTY(EditAnywhere,Category="Stamina")
	float TimeStaminaRecover = 3.0f;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Stamina")
	int32 MaxStamina=40;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Stamina")
	int32 CurrentStamina=40;

	void UpdateStaminaAI();
	void RecoverStamina();

	virtual void Death(ABaseCharacter* Character) override;
	void AfterDeath() const;
	FTimerHandle DeathTimer;
	UPROPERTY(EditAnywhere,Category="Death")
	UAnimMontage* DeathAnimMontage;
	
	UPROPERTY(EditAnywhere,Category="Effect")
	TSubclassOf<AFirstBossEffectActor> CurrentEffectActor;

	UPROPERTY(EditAnywhere,Category="Key")
	TSubclassOf<AKeyActor> CardKey;
	UPROPERTY(EditAnywhere,Category="Key")
	ADoorBaseActor* DoorThatNeedBossKey;
	UPROPERTY(EditAnywhere,Category="Weapon")
	TSubclassOf<ABaseWeapon> NewWeaponClassForPlayer;

	float EndEnemyAttackTime=0.1f;
};
