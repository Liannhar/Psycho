// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/WeaponComponent.h"

#include "BaseCharacter.h"
#include "BaseWeapon.h"

UWeaponComponent::UWeaponComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}


void UWeaponComponent::ChangeWeapon(ABaseWeapon* NewWeapon,TSubclassOf<ABaseWeapon> NewClassOfWeapon)
{
	if(const auto BaseCharacter = GetCharacter())
	{
		if(CurrentWeapon)
		{
			DetachWeaponOfSocket(CurrentWeapon,NewWeapon->GetActorLocation());
			auto NewWeaponLocation = NewWeapon->GetActorLocation();
			CurrentWeapon->DettachWeapon(NewWeaponLocation);
		}
		CurrentWeapon=NewWeapon;
		CurrentClassOfWeapon = NewClassOfWeapon;
		NewWeapon->AttachWeapon();
		AttachWeaponToSocket(CurrentWeapon,BaseCharacter,WeaponSocketName);
		const auto AttackComponent = GetAttackComponent();
		AttackComponent->SetCombo();
	}
}

void UWeaponComponent::SetNewWeapon(TSubclassOf<ABaseWeapon> NewClassOfWeapon)
{
	if(const auto BaseCharacter = GetCharacter())
	{
		CurrentClassOfWeapon = NewClassOfWeapon;
		const auto NewWeapon = GetWorld()->SpawnActor<ABaseWeapon>(CurrentClassOfWeapon);
		if(!NewWeapon) return;
		CurrentWeapon=NewWeapon;
		NewWeapon->AttachWeapon();
		AttachWeaponToSocket(CurrentWeapon,BaseCharacter,WeaponSocketName);
		const auto AttackComponent = GetAttackComponent();
		AttackComponent->SetCombo();
	}
}

ABaseCharacter* UWeaponComponent::GetCharacter() const
{
	const auto Actor = GetOwner();
	if(!Actor) return nullptr;

	const auto BaseCharacter = Cast<ABaseCharacter>(Actor);
	if(!BaseCharacter) return nullptr;

	return BaseCharacter;
}

UAttackComponent* UWeaponComponent::GetAttackComponent() const
{
	const auto BaseCharacter = GetCharacter();
	const auto Component = BaseCharacter->GetComponentByClass(UAttackComponent::StaticClass());
	if(!Component) return nullptr;

	const auto AttackComponent = Cast<UAttackComponent>(Component);
	if(!AttackComponent) return nullptr;

	return AttackComponent;
}



void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	const auto Weapon = GetWorld()->SpawnActor<ABaseWeapon>(CurrentClassOfWeapon);
	if(!Weapon) return;
	
	if(const auto BaseCharacter = GetCharacter())
	{
		Weapon->SetOwner(BaseCharacter);
		AttachWeaponToSocket(Weapon,BaseCharacter,WeaponSocketName);
		CurrentWeapon = Weapon;	
	}
	
}

void UWeaponComponent::AttachWeaponToSocket(ABaseWeapon* Weapon, const ABaseCharacter* Character, const FName& SocketName)
{
	if (!Weapon) return;
	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget,false);
	Weapon->AttachToComponent(Character->GetMesh(),AttachmentRules,SocketName);
}

void UWeaponComponent::DetachWeaponOfSocket(ABaseWeapon* Weapon, FVector NewLocation)
{
	if(!Weapon) return;
	const FDetachmentTransformRules DettachmentRules(EDetachmentRule::KeepWorld,EDetachmentRule::KeepWorld,EDetachmentRule::KeepWorld,false);
	Weapon->DettachWeapon(NewLocation);
	Weapon->DetachFromActor(DettachmentRules);
}


ABaseCharacter* UWeaponComponent::GetCharacter()
{
	const auto Actor = GetOwner();
	if(!Actor) return nullptr;

	const auto BaseCharacter = Cast<ABaseCharacter>(Actor);
	if(!BaseCharacter) return nullptr;
	return BaseCharacter;
}

