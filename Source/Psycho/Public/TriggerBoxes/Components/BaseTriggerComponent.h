// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseTriggerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PSYCHO_API UBaseTriggerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseTriggerComponent();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	virtual void Interact(AActor* OtherActor);
};
