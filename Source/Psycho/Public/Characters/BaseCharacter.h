// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UAttackComponent;
class UWeaponComponent;
class UMotionWarpingComponent;

UCLASS()
class PSYCHO_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Health, meta = (AllowPrivateAccess = "true"))
	class UHealthComponent* HealthComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = "true"))
	UAttackComponent* AttackComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	UWeaponComponent* WeaponComponent;
	UPROPERTY(EditAnywhere,Category="Component")
	UMotionWarpingComponent* MotionWarpingComponent;

public:	
	// Sets default values for this actor's properties
	ABaseCharacter();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Death();

	UPROPERTY(EditAnywhere,Category="Health")
	float LifeSpan = 5.0f;
	UPROPERTY(EditAnywhere,Category="Health")
	float DistanceOfRepulsion= 50.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void GetDamage(AActor* Actor);
};
