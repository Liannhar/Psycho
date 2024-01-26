// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnDeathSignature)
DECLARE_MULTICAST_DELEGATE(FOnTakeDamageStartSignature)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PSYCHO_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Values, meta = (AllowPrivateAccess = "true", ClampMin = "0.0"))
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Values, meta = (AllowPrivateAccess = "true", ClampMin = "0.0"))
	float CurrentHP;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Values, meta = (AllowPrivateAccess = "true"))
	float PercentHP;
	
	float TakeDamageMultiplier;

	void CalculatePercentHP();

	void OnDied();

	bool LastAttackIsHeavy=false;
public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void ApplyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float GetMaxHP();
	float GetCurrentHP();
	float GetPercentHP();
	bool GetLastAttackIsHeavy(){return LastAttackIsHeavy;};

	void SetTakeDamageMultiplier(float Multiplier) { TakeDamageMultiplier = Multiplier; };
	void ResetTakeDamageMultiplier() { TakeDamageMultiplier = 1.f; };

	FOnDeathSignature OnDeath;
	FOnTakeDamageStartSignature OnTakeDamage;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Values)
	bool isInvulnerable;

	UFUNCTION(BlueprintCallable)
	void RestoreHP(float RestoreAmount);
};

