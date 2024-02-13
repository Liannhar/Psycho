// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"
#include "MotionWarpingComponent.h"
#include "AttackComponent.h"
#include "HealthComponent.h"
#include "WeaponComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "P_PlayerController.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

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
	HealthComponent->OnDeath.AddUObject(this,&ABaseCharacter::Death);
}

void ABaseCharacter::Death()
{
	//PlayAnimMontage();// Анимация смерти
	GetCharacterMovement()->DisableMovement();
	if(const auto PlayerController = Cast<AP_PlayerController>(GetController()))
	{
		Controller->DisableInput(PlayerController);
	}
	if(const auto Collision = GetCapsuleComponent())
	{
		Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
	}
}

//здесь персонаж реагирует на урон
void ABaseCharacter::GetDamage(AActor* Actor)
{
	/*//PlayAnimMontage();// Анимация получения урона
	*/
}