// Copyright Epic Games, Inc. All Rights Reserved.


#include "PsychoGameModeBase.h"

#include "CheckPointActor.h"
#include "PsychoSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerCharacter.h"

APsychoGameModeBase::APsychoGameModeBase()
{
	
}

void APsychoGameModeBase::SetFightStatus(bool CurrentStatus)
{
	FightStatus=CurrentStatus;
	OnChangeFightStatus.Broadcast(CurrentStatus);
}

void APsychoGameModeBase::SaveAll(UPsychoSaveGame* Save) const
{
	const auto PlayerActor = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCharacter::StaticClass());
	if(const auto Player = Cast<APlayerCharacter>(PlayerActor))
	{
		Save->SavePlayer(Player);	
	}
	TArray<AActor*> CheckPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACheckPointActor::StaticClass(),CheckPoints);
	for (AActor* Actor : CheckPoints)
	{
		if(const auto CheckPoint= Cast<ACheckPointActor>(Actor))
		{
			Save->SaveCheckPoint(CheckPoint);
		}
	}
	Save->EndSave();
}

void APsychoGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	CurrentSaveGame = Cast<UPsychoSaveGame>(UGameplayStatics::CreateSaveGameObject(UPsychoSaveGame::StaticClass()));
	CurrentSaveGame = CurrentSaveGame->Load();
}
