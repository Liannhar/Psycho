// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackComponent.h"
#include "PsychoSaveGame.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"


class ABaseWeapon;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PSYCHO_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponComponent();
protected:
	virtual void BeginPlay() override;
	static void AttachWeaponToSocket(ABaseWeapon* Weapon, const ABaseCharacter* Character, const FName& SocketName);
	static void DetachWeaponOfSocket(ABaseWeapon* Weapon, FVector NewLocation);

	UPROPERTY(EditDefaultsOnly,Category="Weapon")
	TSubclassOf<ABaseWeapon> CurrentClassOfWeapon;

	UPROPERTY()
	ABaseWeapon* CurrentWeapon=nullptr;
	
	UPROPERTY(EditAnywhere,Category="Weapon")
	FName WeaponSocketName="WeaponSocket";
private:
	ABaseCharacter* GetCharacter();
public:

	ABaseWeapon* GetCurrentWeapon() const {return CurrentWeapon;}
	TSubclassOf<ABaseWeapon> GetCurrentClassOfWeapon() const {return CurrentClassOfWeapon;}
	
	UFUNCTION(BlueprintCallable)
	void ChangeWeapon(ABaseWeapon* NewWeapon,TSubclassOf<ABaseWeapon> NewClassOfWeapon);
	ABaseCharacter* GetCharacter() const;
	UAttackComponent* GetAttackComponent() const;
	void SetNewWeapon(TSubclassOf<ABaseWeapon> NewClassOfWeapon);
};
