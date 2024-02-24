// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackComponent.h"
#include "GameFramework/Actor.h"
#include "Psycho/CoreTypes.h"
#include "BaseWeapon.generated.h"

class UBoxComponent;



UCLASS()
class PSYCHO_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseWeapon();
	float GetLightAttackDamage() const {return LightAttackDamage;}
	float GetHeavyAttackDamage() const {return HeavyAttackDamage;}
	UPROPERTY(EditAnywhere,Category="Combo")
	TArray<FCombination> DifferentCombos;
	virtual void DettachWeapon(FVector NewLocation);
	virtual void AttachWeapon();
	USkeletalMeshComponent* GetSkeletalMeshComponent(){return SkeletalMeshComponent;}
protected:
	UPROPERTY(EditAnywhere,Category="Damage")
	float LightAttackDamage;
	UPROPERTY(EditAnywhere,Category="Damage")
	float HeavyAttackDamage;
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere,Category="Components")
	UBoxComponent* CollisionComponent;
	UPROPERTY(EditAnywhere,Category="Components")
	USkeletalMeshComponent* SkeletalMeshComponent;
};
