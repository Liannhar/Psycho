// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventorySystem/Item.h"
#include "Killkit.generated.h"

/**
 * 
 */
UCLASS()
class PSYCHO_API UKillkit : public UItem
{
	GENERATED_BODY()


protected:
	void Use(APlayerCharacter* Player) override;
};
