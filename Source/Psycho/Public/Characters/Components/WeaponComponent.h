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
	
	ABaseWeapon* GetCurrentWeapon() {return CurrentWeapon;}
	TSubclassOf<ABaseWeapon> GetCurrentWeaponClass() {return WeaponClasses[CurrentWeaponIndex];}
protected:
	virtual void BeginPlay() override;
	void AttachWeaponToSocket(ABaseWeapon* Weapon, ABaseCharacter* Character, const FName& SocketName);
	UPROPERTY(EditDefaultsOnly,Category="Weapon")
	TArray<TSubclassOf<ABaseWeapon>> WeaponClasses;
	UPROPERTY(EditAnywhere,Category="Weapon")
	FName WeaponSocketName="WeaponSocket";
private:
	int32 CurrentWeaponIndex=0;
	UPROPERTY()
	ABaseWeapon* CurrentWeapon = nullptr;
	UPROPERTY()
	TArray<ABaseWeapon*> Weapons;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
