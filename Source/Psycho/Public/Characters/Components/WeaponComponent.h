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
	
	ABaseWeapon* GetCurrentWeapon() const {return CurrentWeapon;}
	
	UFUNCTION(BlueprintCallable)
	void ChangeWeapon(ABaseWeapon* NewWeapon,TSubclassOf<ABaseWeapon> NewClassOfWeapon);
protected:
	virtual void BeginPlay() override;
	static void AttachWeaponToSocket(ABaseWeapon* Weapon, const ABaseCharacter* Character, const FName& SocketName);
	static void DetachWeaponOfSocket(ABaseWeapon* Weapon, FVector NewLocation);

	UPROPERTY(EditDefaultsOnly,Category="Weapon")
	TSubclassOf<ABaseWeapon> CurrentClassOfWeapon;
	
	UPROPERTY(EditAnywhere,Category="Weapon")
	FName WeaponSocketName="WeaponSocket";
private:
	UPROPERTY()
	ABaseWeapon* CurrentWeapon=nullptr;

	ABaseCharacter* GetCharacter();
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
