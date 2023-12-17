// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"

#include "AttackComponent.h"
#include "HealthComponent.h"
#include "WeaponComponent.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("Health Component");
	AttackComponent = CreateDefaultSubobject<UAttackComponent>("Attack Component");
	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>("Weapon Component");
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
