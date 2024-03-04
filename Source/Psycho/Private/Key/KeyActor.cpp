// Fill out your copyright notice in the Description page of Project Settings.


#include "Key/KeyActor.h"

#include "Components/BoxComponent.h"

AKeyActor::AKeyActor()
{
	PrimaryActorTick.bCanEverTick = false;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(StaticMesh);
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>("Box component");

	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComponent->SetupAttachment(RootComponent);
}

void AKeyActor::EnablePhysics()
{
	StaticMesh->SetSimulatePhysics(true);
	if(GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(PhysicsTimer,this,&AKeyActor::DisablePhysics,TimeForFall);
	}
}

void AKeyActor::DisablePhysics()
{
	StaticMesh->SetSimulatePhysics(false);
}

void AKeyActor::BeginPlay()
{
	Super::BeginPlay();
}

