// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/BaseWeapon.h"

#include "NiagaraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

ABaseWeapon::ABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("Skeletal Mesh");
	SetRootComponent(SkeletalMeshComponent);
	InteractLightNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("InteractLight");
	InteractLightNiagaraComponent->SetupAttachment(RootComponent);
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>("Box component");
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComponent->SetupAttachment(RootComponent);
}

void ABaseWeapon::DettachWeapon(FVector& NewLocation)
{
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractLightNiagaraComponent->SetVisibility(true);
}

void ABaseWeapon::AttachWeapon()
{
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	InteractLightNiagaraComponent->SetVisibility(false);
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
		CollisionComponent->Deactivate();
	}
}

