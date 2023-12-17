// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackComponent.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"


class ABaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PSYCHO_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponComponent();
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Weapon")
	ABaseWeapon* CurrentWeapon;
protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	FOnStartAttack OnStartAttack;
	FOnEndAttack OnEndAttack;
	void StartAttack();
	void EndAttack();
		
};
