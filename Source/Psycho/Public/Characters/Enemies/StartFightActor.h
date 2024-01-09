// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StartFightActor.generated.h"

class UBoxComponent;

UCLASS()
class PSYCHO_API AStartFightActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AStartFightActor();
	
protected:
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	bool FightWasStarted = false;

	UPROPERTY(EditAnywhere,Category="Collision")
	UBoxComponent* BoxComponent;
};
