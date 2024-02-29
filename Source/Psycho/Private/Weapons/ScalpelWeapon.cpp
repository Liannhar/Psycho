// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/ScalpelWeapon.h"

AScalpelWeapon::AScalpelWeapon()
{
	HeavyAttackDamage = 20.0f;
	LightAttackDamage = 10.0f;
}

void AScalpelWeapon::DettachWeapon(FVector NewLocation)
{
	Super::DettachWeapon(NewLocation);
	SetActorLocation(NewLocation);
	SetActorRotation(FRotator(0.0f,0.0f,0.0f));
	
}

void AScalpelWeapon::AttachWeapon()
{
	Super::AttachWeapon();
	SkeletalMeshComponent->SetWorldScale3D(FVector(1.0f,1.0f,1.0f));
}
