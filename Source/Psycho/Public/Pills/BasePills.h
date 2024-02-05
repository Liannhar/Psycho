// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Player/PlayerCharacter.h"
#include "BasePills.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PSYCHO_API UBasePills : public UObject
{
	GENERATED_BODY()

public:
	virtual void UsePill();
	virtual void Init(UTexture2D* NewIcon);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Icon)
	class UTexture2D* Icon;
protected:
	class APlayerCharacter* Player;
	
	FTimerHandle PillEffectsTimer;
	FTimerHandle PillAfterEffectsTimer;
};
