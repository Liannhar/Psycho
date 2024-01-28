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

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void ApplyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Values, meta = (AllowPrivateAccess = "true", ClampMin = "0.0"))
	float MaxHP=100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Values, meta = (AllowPrivateAccess = "true", ClampMin = "0.0"))
	float CurrentHP=100.0f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Values, meta = (AllowPrivateAccess = "true"))
	float PercentHP;

	void CalculatePercentHP();

	void OnDied();

	bool LastAttackIsHeavy=false;

	bool CharacterIsDead=false;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float GetMaxHP();
	void SetMaxHP(float NewMaxHP){MaxHP=NewMaxHP;}
	float GetCurrentHP();
	void SetCurrentHP(float NewCurrentHP){CurrentHP=NewCurrentHP;}
	float GetPercentHP();
	bool GetLastAttackIsHeavy() const {return LastAttackIsHeavy;}

	UFUNCTION(BlueprintCallable)
	bool IsDead(){return CharacterIsDead;}	

	FOnDeathSignature OnDeath;
	FOnTakeDamageStartSignature OnTakeDamage;

	UFUNCTION(BlueprintCallable)
	void RestoreHP(float RestoreAmount);
};

