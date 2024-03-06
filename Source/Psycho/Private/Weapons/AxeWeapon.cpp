// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/AxeWeapon.h"

AAxeWeapon::AAxeWeapon()
{
	HeavyAttackDamage = 40.0f;
	LightAttackDamage = 20.0f;
}

void AAxeWeapon::AttachWeapon()
{
	Super::AttachWeapon();
}

void AAxeWeapon::DettachWeapon(FVector& NewLocation)
{
	Super::DettachWeapon(NewLocation);
	SetActorLocation(NewLocation);
	SetActorRotation(FRotator(0.0f,0.0f,0.0f));
}
