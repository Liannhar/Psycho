// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TriggerBoxes/BaseTriggerBox.h"
#include "CanStartFightTriggerBox.generated.h"


class AStartFightActor;

UCLASS()
class PSYCHO_API ACanStartFightTriggerBox : public ABaseTriggerBox
{
	GENERATED_BODY()
protected:
	virtual void Action() override;

	UPROPERTY(EditAnywhere,Category="StartFightActor")
	AStartFightActor* StartFightActor;
};
