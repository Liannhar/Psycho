// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Psycho/CoreTypes.h"
#include "BaseEnemy.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;

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
	virtual void Attack();
	
	bool GetNotIsAttackingNow() const {return NotIsAttackingNow;}
	bool GetIsTakenDamage() const {return IsTakenDamage;}
	bool GetLastAttackIsHeavy() const;

	void PreparationsBeforeTheAttack(EComboInput Type,int32 NewCombo,int32 NewCount,bool NeedRandomCount=false);
	void ChangeMaxSpeed(float NewSpeed) const;
	void BlockAttack();

	void Deactivate();
	void Reactivate();

	virtual void BeginPlay() override;

	void SetStartAttack();
	void SetCanAttack(bool NewBool) const;

	float GetBaseSpeed() const {return BaseSpeed;}
	

protected:
	UPROPERTY()
	bool IsTakenDamage = false;
	
	virtual void GetDamage(AActor* Actor) override;

	UPROPERTY()
	AController* OwnController;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Speed")
	float BaseSpeed = 600.0f;
	
	void EndWait();
	UPROPERTY(EditAnywhere,Category="Damage")
	float TimeForWaitDamage=4.0f;
	UPROPERTY(EditAnywhere,Category="Damage")
	float TimeForEndNiagara=1.0f;
	UPROPERTY()
	int32 AttacksCount=0;
	UPROPERTY()
	int32 ComboIndex = 0;

	UPROPERTY(EditAnywhere,Category="Health")
	float DistanceOfRepulsion= 20.0f;
	
	EComboInput AttackType=None;
	
	FTimerHandle WaitNextAttemptAttack;
	
	FTimerHandle EndNiagaraEffectTimer;

	FTimerHandle EndDamageEffectTimer;
	
	bool NotIsAttackingNow=true;

	virtual void Death() override;

	void EndDamageEffects();
	void EndNiagaraEffect();

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Materials")
	TArray<UMaterialInterface*> MaterialsChangedForDamaged;
	
	UPROPERTY()
	TArray<UMaterialInterface*> OldMaterials;

	UPROPERTY(EditAnywhere,Category="Niagara")
	UNiagaraComponent* SmokeNiagaraComponent;
	UPROPERTY(EditAnywhere,Category="Niagara")
	UNiagaraSystem* NewNiagaraSystem;
	UPROPERTY()
	UNiagaraSystem* OldNiagaraSystem;
};
