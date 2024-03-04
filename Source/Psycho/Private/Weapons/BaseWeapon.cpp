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
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ABaseWeapon::AttachWeapon()
{
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABaseWeapon::EnablePhysics()
{
	SkeletalMeshComponent->SetSimulatePhysics(true);
	if(GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(PhysicsTimer,this,&ABaseWeapon::DisablePhysics,TimeForFall);
	}
}

void ABaseWeapon::DisablePhysics()
{
	SkeletalMeshComponent->SetSimulatePhysics(false);
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

