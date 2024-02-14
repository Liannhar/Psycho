// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemies/BaseEnemy.h"
#include "FirstBossEnemy.generated.h"


class AFirstBossEffectActor;

UCLASS()
class PSYCHO_API AFirstBossEnemy : public ABaseEnemy
{
	GENERATED_BODY()
public:
	void StartEffectMoving(int32 NewStaminaCost);
	void EndEffectMoving();
	
	void ChangeStaminaCost(int32 NewCost);
	virtual void Attack() override;
	void PreparationBossBeforeAttack(const EComboInput Type, const int32 NewCombo, const int32 NewCount, const bool NeedRandomCount,const int32 NewStaminaCost);

	int32 GetCurrentStamina() const {return CurrentStamina;}
protected:
	FTimerHandle EffectTImer;
	UPROPERTY(EditAnywhere,Category="Effect")
	float EffectTime = 0.5f;

	void MakeEffect();

	virtual void BeginPlay() override;

	FTimerHandle StaminaRecoverTimer;
	UPROPERTY(EditAnywhere,Category="Stamina")
	float TimeStaminaRecover = 3.0f;
	
	UPROPERTY(EditAnywhere,Category="Stamina")
	int32 MaxStamina=30;

	UPROPERTY(EditAnywhere,Category="Stamina")
	int32 CurrentStamina=0;

	void RecoverStamina();
	
	UPROPERTY(EditAnywhere,Category="Effect")
	TSubclassOf<AFirstBossEffectActor> CurrentEffectActor;
};
