// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseTriggerBox.generated.h"

class UBoxComponent;

UCLASS()
class PSYCHO_API ABaseTriggerBox : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseTriggerBox();

protected:
	virtual void BeginPlay() override;
	virtual void Action();
	virtual void End();
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
	UPROPERTY(EditAnywhere,Category="Collision")
	UBoxComponent* BoxComponent;
};
