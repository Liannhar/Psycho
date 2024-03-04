// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorBaseActor.generated.h"

UCLASS()
class PSYCHO_API ADoorBaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADoorBaseActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="PinCode")
	bool NeedPinCode=false;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="PinCode")
	bool CanInteract=false;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="PinCode")
	bool NeedKey=false;
};
