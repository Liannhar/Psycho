// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/AxeWeapon.h"

AAxeWeapon::AAxeWeapon()
{
	HeavyAttackDamage = 40.0f;
	LightAttackDamage = 20.0f;
}

void AAxeWeapon::EnablePhysics(FVector NewLocation)
{
	Super::EnablePhysics(NewLocation);
	SetActorLocation(NewLocation);
	SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
	
}

void AAxeWeapon::DisablePhysics()
{
	Super::DisablePhysics();
	SkeletalMeshComponent->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
}

