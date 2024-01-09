// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGame/CheckPointActor.h"

#include "PsychoSaveGame.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerCharacter.h"
#include "Psycho/PsychoGameModeBase.h"

ACheckPointActor::ACheckPointActor()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bCanEverTick = false;
	BoxComponent=CreateDefaultSubobject<UBoxComponent>("Box Collision");
	BoxComponent->SetBoxExtent(FVector(32.0f,32.0f,32.0f));
}


void ACheckPointActor::BeginPlay()
{
	Super::BeginPlay();
	LoadGame();
}

void ACheckPointActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	const auto PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if(PlayerCharacter && NotUsed)
	{
		UPsychoSaveGame* Save = Cast<UPsychoSaveGame>(UGameplayStatics::CreateSaveGameObject(UPsychoSaveGame::StaticClass()));
		const auto World =GetWorld();
		if(Save && World)
		{
			if(const auto GameMode = Cast<APsychoGameModeBase>(World->GetAuthGameMode()))
			{
				NotUsed=false;	
				GameMode->SaveAll(Save);
			}
			
		}
				
	}
}

void ACheckPointActor::LoadGame()
{
	const auto GameMode = Cast<APsychoGameModeBase>(GetWorld()->GetAuthGameMode());
	if(GameMode)
	{
		const auto SaveGame = GameMode->GetCurrentSaveGame();
		if(SaveGame)
		{
			const auto CheckPointSave = SaveGame->GetCheckPointSave();
			SetActorLocation(CheckPointSave.CheckPointLocation);
			NotUsed=CheckPointSave.CheckPointNotUsed;
		}
	}
}






