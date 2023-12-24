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
	if(WeaponClasses.Num()==0) return;
	for(auto WeaponClass : WeaponClasses)
	{
		auto Weapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass);
		if(!Weapon) continue;
		const auto Actor = GetOwner();
		if(!Actor) return;

		const auto BaseCharacter = Cast<ABaseCharacter>(Actor);
		if(!BaseCharacter) return;
		
		Weapon->SetOwner(BaseCharacter);
		Weapons.Add(Weapon);
		AttachWeaponToSocket(Weapon,BaseCharacter,WeaponSocketName);
	}
	CurrentWeapon = Weapons[CurrentWeaponIndex];
}

void UWeaponComponent::AttachWeaponToSocket(ABaseWeapon *Weapon, ABaseCharacter *Character, const FName& SocketName)
{
	if (!Weapon) return;

	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget,false);
	Weapon->AttachToComponent(Character->GetMesh(),AttachmentRules,SocketName);
}


void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UWeaponComponent::StartAttack()
{
	CurrentWeapon->StartAttack();
}

void UWeaponComponent::EndAttack() const
{
	CurrentWeapon->EndAttack();
}

