// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/BaseWeapon.h"
#include "AxeWeapon.generated.h"


UCLASS()
class PSYCHO_API AAxeWeapon : public ABaseWeapon
{
	GENERATED_BODY()
public:
	AAxeWeapon();
	virtual void AttachWeapon() override;
	virtual void DettachWeapon(FVector& NewLocation) override;
};


