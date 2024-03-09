// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/BaseWeapon.h"
#include "KatanaWeapon.generated.h"


UCLASS()
class PSYCHO_API AKatanaWeapon : public ABaseWeapon
{
	GENERATED_BODY()
public:
	AKatanaWeapon();
	virtual void EnablePhysics(FVector NewLocation) override;
	virtual void DisablePhysics() override;
};