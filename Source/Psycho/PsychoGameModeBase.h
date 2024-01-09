// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PsychoGameModeBase.generated.h"

class UPsychoSaveGame;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnChangeFightStatus, bool)

/**
 * BaseGameMode in all Game
 */
UCLASS()
class PSYCHO_API APsychoGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	APsychoGameModeBase();

	FOnChangeFightStatus OnChangeFightStatus;
	
	UFUNCTION(BlueprintCallable)
	void SetFightStatus(bool CurrentStatus);

	UPsychoSaveGame* GetCurrentSaveGame() const {return CurrentSaveGame;}

	void SaveAll(UPsychoSaveGame* Save) const ;
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere,Category="FightStatus")
	bool FightStatus=false;
	UPROPERTY()
	UPsychoSaveGame* CurrentSaveGame;
};
