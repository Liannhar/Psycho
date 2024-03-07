// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Psycho/CoreTypes.h"
#include "BaseEnemy.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;
class UBehaviorTree;

DECLARE_DYNAMIC_DELEGATE(FOnPlayerDiedSignature);

UCLASS()
class PSYCHO_API ABaseEnemy : public ABaseCharacter
{
	GENERATED_BODY()
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
	void ChangeMaxSpeed(const float& NewSpeed) const;
	static void BlockAttack();

	void Deactivate(float SpeedReduceMultiplier);
	void Reactivate();

	virtual void BeginPlay() override;

	void SetStartAttack();
	void SetCanAttack(const bool& NewBool) const;

	float GetBaseSpeed() const {return BaseSpeed;}

	UFUNCTION()
	void OnPlayerDied();

	UPROPERTY(BlueprintReadWrite)
	FOnPlayerDiedSignature PlayerDied;
protected:
	UPROPERTY()
	bool IsTakenDamage = false;

	virtual void GetDamage(AActor* Actor,const UDamageType* DamageType) override;

	UPROPERTY()
	AController* OwnController;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Speed")
	float BaseSpeed = 600.0f;

	float EndEnemyAttackTime=3.0f;
	void EndWait();
	UPROPERTY(EditAnywhere,Category="Damage")
	float TimeForWaitDamage=4.0f;
	UPROPERTY()
	int32 AttacksCount=0;
	UPROPERTY()
	int32 ComboIndex = 0;

	float DefaultMaxWalkSpeed;

	UPROPERTY(EditAnywhere,Category="Health")
	float DistanceOfRepulsion= 20.0f;
	
	EComboInput AttackType=None;
	
	FTimerHandle WaitNextAttemptAttack;
	
	int32 AttackDirection=0;

	FTimerHandle EndDamageEffectTimer;
	
	bool NotIsAttackingNow=true;

	virtual void Death() override;

	void EndDamageEffects();
	
	void DamageDecalCreate(const bool& ActorRotationIsHead) const;
	UPROPERTY(EditAnywhere,Category="Decal")
	float DamageDecalLocationZUPLimit = 112.0f;
	UPROPERTY(EditAnywhere,Category="Decal")
	float DamageDecalLocationZDownLimit = 84.0f;
	UPROPERTY(EditAnywhere,Category="Decal")
	float DamageDecalLocationYLeftLimitHead = 7.0f;
	UPROPERTY(EditAnywhere,Category="Decal")
	float DamageDecalLocationYRightLimitHead = 13.0f;
	UPROPERTY(EditAnywhere,Category="Decal")
	float DamageDecalLocationYLeftLimitBack = -3.0f;
	UPROPERTY(EditAnywhere,Category="Decal")
	float DamageDecalLocationYRightLimitBack = -5.0f;
	UPROPERTY(EditAnywhere,Category="Decal")
	float DamageDecalLocationXLimit = -5.0f;
	FTimerHandle DamageDecalTimer;
	float EndDamageDecalTime;
	UPROPERTY(EditAnywhere,Category="Decal")
	UMaterialInterface* DamageDecalMaterialInterface;

	UPROPERTY(EditAnywhere,Category="Decal")
	FVector DecalSizeVector =FVector(7.0f, 4.0f, 14.0f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Collision", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* EnemyChannelCollision;
};
