// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/WeaponComponent.h"

#include "BaseCharacter.h"
#include "BaseWeapon.h"

UWeaponComponent::UWeaponComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

}


void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	OnStartAttack.AddUObject(this,&UWeaponComponent::StartAttack);
	OnEndAttack.AddUObject(this,&UWeaponComponent::EndAttack);
}


void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UWeaponComponent::StartAttack()
{
	CurrentWeapon->StartAttack();
	const auto Actor = GetOwner();
	if(!Actor) return;

	const auto BaseCharacter = Cast<ABaseCharacter>(Actor);
	if(!BaseCharacter) return;

	const auto AttackComponent = BaseCharacter->GetComponentByClass(UAttackComponent::StaticClass());
	if(!AttackComponent) return;
}

void UWeaponComponent::EndAttack()
{
	CurrentWeapon->EndAttack();
}

