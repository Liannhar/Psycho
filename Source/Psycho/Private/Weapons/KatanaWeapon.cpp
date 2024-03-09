// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/KatanaWeapon.h"

AKatanaWeapon::AKatanaWeapon()
{
	HeavyAttackDamage = 45.0f;
	LightAttackDamage = 25.0f;
}

void AKatanaWeapon::AttachWeapon()
{
	Super::AttachWeapon();
}

void AKatanaWeapon::DettachWeapon(FVector& NewLocation)
{
	Super::DettachWeapon(NewLocation);
	SetActorLocation(NewLocation);
	SetActorRotation(FRotator(0.0f,0.0f,0.0f));
}
