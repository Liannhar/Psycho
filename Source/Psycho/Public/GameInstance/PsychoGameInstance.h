// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PsychoGameInstance.generated.h"

class UPsychoSaveGame;
/**
 * 
 */
UCLASS()
class PSYCHO_API UPsychoGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
protected:
	UPROPERTY()
	UPsychoSaveGame* CurrentSaveGame;
};
