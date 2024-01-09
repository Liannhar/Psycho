// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreTypes.h"
#include "GameFramework/SaveGame.h"
#include "Psycho/CoreTypes.h"
#include "PsychoSaveGame.generated.h"

class ACheckPointActor;
class APlayerCharacter;
class ABaseWeapon;
/**
 * Класс для сохранения игры
 */
UCLASS()
class PSYCHO_API UPsychoSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPsychoSaveGame();
protected:
	UPROPERTY(EditAnywhere,Category="Save")
	FPlayerSave PlayerSave;
	UPROPERTY(EditAnywhere,Category="Save")
	FCheckPointSave CheckPointSave;
public:
	FPlayerSave GetPlayerSave() const {return PlayerSave;}
	FCheckPointSave GetCheckPointSave() const {return CheckPointSave;}

	void SavePlayer(const APlayerCharacter* Player);
	void SaveCheckPoint(const ACheckPointActor* CheckPointActor);
	
	UPsychoSaveGame* Load();
	void EndSave();
};
