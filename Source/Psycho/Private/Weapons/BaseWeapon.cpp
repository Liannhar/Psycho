// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/BaseWeapon.h"

#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

ABaseWeapon::ABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>("Box component");
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("Skeletal Mesh");
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SetRootComponent(SkeletalMeshComponent);
	CollisionComponent->SetupAttachment(RootComponent);
}

void ABaseWeapon::DettachWeapon(FVector NewLocation)
{
	//SkeletalMeshComponent->SetSimulatePhysics(true);
	CollisionComponent->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
}

void ABaseWeapon::AttachWeapon()
{
	//SkeletalMeshComponent->SetSimulatePhysics(false);
	CollisionComponent->SetCollisionResponseToChannel(ECC_Visibility,ECR_Ignore);
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	if(GetAttachParentActor())
	{
		UE_LOG(LogTemp,Display,TEXT("%s"),*GetAttachParentActor()->GetName());
		CollisionComponent->Deactivate();
	}
}

