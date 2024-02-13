// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/BaseWeapon.h"

#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

ABaseWeapon::ABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>("Capsule component");
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("Skeletal Mesh");
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SetRootComponent(SkeletalMeshComponent);
	CollisionComponent->SetupAttachment(RootComponent);
}

void ABaseWeapon::EnablePhysics(FVector NewLocation)
{
	//SkeletalMeshComponent->SetSimulatePhysics(true);
}

void ABaseWeapon::DisablePhysics()
{
	//SkeletalMeshComponent->SetSimulatePhysics(false);
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

