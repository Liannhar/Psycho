// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGame/PsychoSaveGame.h"

#include "BaseWeapon.h"
#include "CheckPointActor.h"
#include "HealthComponent.h"
#include "WeaponComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerCharacter.h"

UPsychoSaveGame::UPsychoSaveGame()
{
	
}

void UPsychoSaveGame::SavePlayer(const APlayerCharacter* Player)
{
	PlayerSave.PlayerLocation=Player->GetActorLocation();
	PlayerSave.CurrentPlayerHP = Player->GetHealthComponent()->GetCurrentHP();
	PlayerSave.CurrentPlayerMaxHP = Player->GetHealthComponent()->GetMaxHP();
	PlayerSave.CurrentPlayerClassOfWeapon = Player->GetWeaponComponent()->GetCurrentClassOfWeapon();
}

void UPsychoSaveGame::SaveCheckPoint(const ACheckPointActor* CheckPointActor)
{
	CheckPointSave.CheckPointLocation = CheckPointActor->GetActorLocation();
	CheckPointSave.CheckPointNotUsed = CheckPointActor->NotUsed;
}

void UPsychoSaveGame::EndSave()
{
	UGameplayStatics::SaveGameToSlot(this,TEXT("PsychoSaveSlot0"),0);
}

UPsychoSaveGame* UPsychoSaveGame::Load()
{
	return Cast<UPsychoSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("PsychoSaveSlot0"),0));
}

