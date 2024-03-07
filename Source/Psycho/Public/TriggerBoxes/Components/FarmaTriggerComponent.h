// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TriggerBoxes/Components/BaseTriggerComponent.h"
#include "FarmaTriggerComponent.generated.h"

class AStartFightActor;
/**
 * 
 */
UCLASS()
class PSYCHO_API UFarmaTriggerComponent : public UBaseTriggerComponent
{
	GENERATED_BODY()
public:
	virtual void Interact(AActor* OtherActor) override;

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Trigger")
	AStartFightActor* TriggeredStartFightActor;
};
