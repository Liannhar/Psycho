// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TriggerBoxes/BaseTriggerBox.h"
#include "TutorialTrigger.generated.h"

/**
 * 
 */
UCLASS()
class PSYCHO_API ATutorialTrigger : public ABaseTriggerBox
{
	GENERATED_BODY()
public:
	ATutorialTrigger();

	virtual void BeginPlay() override;
	virtual void Action() override;
	virtual void End() override;
	virtual void DestroyTrigger();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UTutorialWidgetComponent> TutorialWidgetComponentClass;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	class UTutorialWidgetComponent* TutorialWidgetComponent;
};
