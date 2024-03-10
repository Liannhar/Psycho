// Fill out your copyright notice in the Description page of Project Settings.


#include "SwitchLight/SwitchLightActor.h"

#include "NiagaraComponent.h"
#include "Components/BoxComponent.h"

ASwitchLightActor::ASwitchLightActor()
{
	PrimaryActorTick.bCanEverTick = false;
	SceneComponent=CreateDefaultSubobject<USceneComponent>("SceneComponent");
	RootComponent=SceneComponent;
	CollisionComponent= CreateDefaultSubobject<UBoxComponent>("Collision");
	CollisionComponent->SetupAttachment(RootComponent);
	StaticMesh=CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	StaticMesh->SetupAttachment(RootComponent);
	InteractLight= CreateDefaultSubobject<UNiagaraComponent>("Interact Light");
	InteractLight->SetupAttachment(RootComponent);
}

void ASwitchLightActor::BeginPlay()
{
	Super::BeginPlay();
	SwitchLight(false);
}

void ASwitchLightActor::SwitchLight(const bool SwitchBool)
{
	NeedUse=SwitchBool;
	if(NeedUse)
	{
		CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		InteractLight->SetVisibility(SwitchBool);
	}
	else
	{
		OnSwitchLight.Broadcast(this);
		CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		InteractLight->SetVisibility(SwitchBool);
	}
}
