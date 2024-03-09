// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/KatanaWeapon.h"

AKatanaWeapon::AKatanaWeapon()
{
	HeavyAttackDamage = 45.0f;
	LightAttackDamage = 25.0f;
}

void AKatanaWeapon::EnablePhysics(FVector NewLocation)
{
	Super::EnablePhysics(NewLocation);
	SetActorLocation(NewLocation);
	SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));

}

void AKatanaWeapon::DisablePhysics()
{
	Super::DisablePhysics();
	SkeletalMeshComponent->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
}
