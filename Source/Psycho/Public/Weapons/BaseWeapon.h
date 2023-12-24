// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackComponent.h"
#include "GameFramework/Actor.h"
#include "Psycho/CoreTypes.h"
#include "BaseWeapon.generated.h"

class UCapsuleComponent;



UCLASS()
class PSYCHO_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseWeapon();
	void StartAttack();
	void EndAttack();
	UPROPERTY(EditAnywhere,Category="Combo")
	TArray<FCombination> DifferentCombos;
protected:
	
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere,Category="Components")
	UCapsuleComponent* CollisionComponent;
	UPROPERTY(VisibleAnywhere,Category="Components")
	USkeletalMeshComponent* SkeletalMeshComponent;
		
private:
	bool IsAttacking = false;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
