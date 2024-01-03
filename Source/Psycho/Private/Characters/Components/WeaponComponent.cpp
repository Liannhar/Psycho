// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/WeaponComponent.h"

#include "BaseCharacter.h"
#include "BaseWeapon.h"

UWeaponComponent::UWeaponComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

}


void UWeaponComponent::ChangeWeapon(ABaseWeapon* NewWeapon,TSubclassOf<ABaseWeapon> NewClassOfWeapon)
{
	if(const auto BaseCharacter = GetCharacter())
	{
		DetachWeaponOfSocket(CurrentWeapon,NewWeapon->GetActorLocation());
		CurrentWeapon=NewWeapon;
		CurrentClassOfWeapon = NewClassOfWeapon;
		NewWeapon->DisablePhysics();
		AttachWeaponToSocket(CurrentWeapon,BaseCharacter,WeaponSocketName);
	}
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	const auto Weapon = GetWorld()->SpawnActor<ABaseWeapon>(CurrentClassOfWeapon);
	if(!Weapon) return;;
	
	if(const auto BaseCharacter = GetCharacter())
	{
		Weapon->SetOwner(BaseCharacter);
		AttachWeaponToSocket(Weapon,BaseCharacter,WeaponSocketName);
		CurrentWeapon = Weapon;	
	}
	
}

void UWeaponComponent::AttachWeaponToSocket(ABaseWeapon *Weapon, const ABaseCharacter *Character, const FName& SocketName)
{
	if (!Weapon) return;
	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget,false);
	Weapon->AttachToComponent(Character->GetMesh(),AttachmentRules,SocketName);
}

void UWeaponComponent::DetachWeaponOfSocket(ABaseWeapon* Weapon, FVector NewLocation)
{
	if(!Weapon) return;
	const FDetachmentTransformRules DettachmentRules(EDetachmentRule::KeepWorld,EDetachmentRule::KeepWorld,EDetachmentRule::KeepWorld,false);
	Weapon->EnablePhysics(NewLocation);
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

void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

