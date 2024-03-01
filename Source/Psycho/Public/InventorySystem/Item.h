// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Player/PlayerCharacter.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable, EditInLineNew, DefaultToInstanced)
class PSYCHO_API UItem : public UObject
{
	GENERATED_BODY()
	
public:
	UItem();

	virtual UWorld* GetWorld() const override
	{
		return World;
	}

	UPROPERTY(Transient)
	UWorld* World;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	UStaticMesh* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	UTexture2D* Icon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta=(Multyline=true))
	FText Description;

	UFUNCTION(BlueprintCallable, Category = "Item")
	virtual void Use(APlayerCharacter* Player);
};
