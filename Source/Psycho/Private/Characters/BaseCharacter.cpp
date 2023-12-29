// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Characters/BaseCharacter.h"
#include "MotionWarpingComponent.h"
#include "AttackComponent.h"
#include "HealthComponent.h"
#include "WeaponComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

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
	HealthComponent->OnDeath.AddUObject(this,&ABaseCharacter::Death);
}

void ABaseCharacter::Death()
{
	//PlayAnimMontage();// Анимация смерти
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(LifeSpan);
	if(const auto Collision = GetCapsuleComponent())
	{
		Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
	}
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
//здесь персонаж реагирует на урон
void ABaseCharacter::GetDamage(AActor* Actor)
{
	//PlayAnimMontage();// Анимация получения урона
	const auto DamageActorForwardVector = Actor->GetActorForwardVector();
	const auto ActorForwardVector = GetActorForwardVector();
	const auto DotProduct = FVector::DotProduct(DamageActorForwardVector, ActorForwardVector);
	if(DotProduct>0.0f)
	{
		SetActorLocation(GetActorLocation()+(ActorForwardVector+DamageActorForwardVector)*DistanceOfRepulsion);
	}
	else
	{
		SetActorLocation(GetActorLocation()+(-1*ActorForwardVector+DamageActorForwardVector)*DistanceOfRepulsion);
	}
}