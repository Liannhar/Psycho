// Fill out your copyright notice in the Description page of Project Settings.


#include "Pills/BasePillActor.h"
#include "Structures/PillsDataStructure.h"
#include "Characters/Player/PlayerCharacter.h"
#include "Characters/Components/PillsComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePillActor::ABasePillActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

void ABasePillActor::BeginPlay()
{
	Super::BeginPlay();

}

void ABasePillActor::OnInteract(APlayerCharacter* Player)
{
	if (!Player && !PillData) return;

	Player->GetPillsComponent()->AddPill(PillData);

	Destroy();
}


void ABasePillActor::PostEditChangeProperty(FPropertyChangedEvent& E)
{
	Super::PostEditChangeProperty(E);

	FName PropertyName = (E.Property != NULL) ? E.Property->GetFName() : NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(ABasePillActor, PillData))
	{
		Mesh->SetStaticMesh(PillData ? PillData->GetMesh() : nullptr);
	}

}
