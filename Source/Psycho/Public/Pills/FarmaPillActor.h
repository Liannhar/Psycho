// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pills/BasePillActor.h"
#include "FarmaPillActor.generated.h"

class UFarmaTriggerComponent;
/**
 * 
 */
UCLASS()
class PSYCHO_API AFarmaPillActor : public ABasePillActor
{
	GENERATED_BODY()
public:
	AFarmaPillActor();
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Components")
	UFarmaTriggerComponent* FirmaTriggerComponent;
};
