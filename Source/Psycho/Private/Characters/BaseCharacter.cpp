// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Characters/BaseCharacter.h"
#include "MotionWarpingComponent.h"
#include "AttackComponent.h"
#include "HealthComponent.h"
#include "WeaponComponent.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("Health Component");
	AttackComponent = CreateDefaultSubobject<UAttackComponent>("Attack Component");
	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>("Weapon Component");
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>("MotionWarping Component");
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(HealthComponent);
	check(AttackComponent);
	check(WeaponComponent);
	AttackComponent->SetCombo();
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
