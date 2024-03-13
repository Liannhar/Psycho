// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


class ABaseCharacter;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnDeathSignature, ABaseCharacter*);
DECLARE_MULTICAST_DELEGATE(FOnTakeDamageStartSignature);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PSYCHO_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere,Category="Animations")
	UAnimMontage* TakingDamageBackAnimMontage;
	UPROPERTY(EditAnywhere,Category="Animations")
	UAnimMontage* TakingDamageLeftAnimMontage;
	UPROPERTY(EditAnywhere,Category="Animations")
	UAnimMontage* TakingDamageRightAnimMontage;
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Values, meta = (AllowPrivateAccess = "true", ClampMin = "0.0"))
	float MaxHP=100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Values, meta = (AllowPrivateAccess = "true", ClampMin = "0.0"))
	float CurrentHP=100.0f;

	float TakeDamageMultiplier;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Values, meta = (AllowPrivateAccess = "true"))
	float PercentHP;

	void CalculatePercentHP();

	void OnDied();

	bool LastAttackIsHeavy=false;

	bool CharacterIsDead=false;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	float GetMaxHP();
	void SetMaxHP(const float NewMaxHP){MaxHP=NewMaxHP;}
	UFUNCTION(BlueprintCallable)
	float GetCurrentHP();
	void SetCurrentHP(const float NewCurrentHP){CurrentHP=NewCurrentHP;}
	UFUNCTION(BlueprintCallable)
	float GetPercentHP();
	
	bool GetLastAttackIsHeavy() const {return LastAttackIsHeavy;};

	void SetTakeDamageMultiplier(float Multiplier) { TakeDamageMultiplier = Multiplier; };
	void ResetTakeDamageMultiplier() { TakeDamageMultiplier = 1.f;}
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Values)
	bool bIsInvulnerable=false;
	UFUNCTION(BlueprintCallable)
	bool IsDead() const {return CharacterIsDead;}	

	FOnDeathSignature OnDeath;
	FOnTakeDamageStartSignature OnTakeDamage;
	
	UFUNCTION(BlueprintCallable)
	void RestoreHP(float RestoreAmount);

	UAnimMontage* GetTakeDamageAnimMontage(const int32& Direction) const;

	UFUNCTION()
	void ApplyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
	
};

