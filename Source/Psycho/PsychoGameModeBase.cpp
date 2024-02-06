// Copyright Epic Games, Inc. All Rights Reserved.


#include "PsychoGameModeBase.h"

#include "CheckPointActor.h"
#include "PsychoSaveGame.h"
#include "StartFightActor.h"
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

void APsychoGameModeBase::CheckEnemySpawners() const
{
	if(CurrentStartFightActor)
	{
		CurrentStartFightActor->CheckEnemySpawners();
	}
}

void APsychoGameModeBase::ChangeEnemiesCount(ABaseEnemy* Enemy, const bool Add)
{
	if(Add)
	{
		EnemiesInBattle.Add(Enemy);
		return;
	}
	UE_LOG(LogTemp,Display,TEXT("Enemies in battle %d"),EnemiesInBattle.Num());

	if(EnemiesInBattle.Contains(Enemy))
	{
		EnemiesInBattle.Remove(Enemy);
	}
	if(EnemiesInBattle.Num()==0)
	{
		CheckEnemySpawners();
	}
}
