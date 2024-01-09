// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckPointActor.generated.h"

class ABaseCharacter;
class UBoxComponent;

UCLASS()
class PSYCHO_API ACheckPointActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACheckPointActor();

	UPROPERTY(EditAnywhere,Category="Collision")
	bool NotUsed=false;
	
protected:
	void LoadGame();
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere,Category="Collision")
	UBoxComponent* BoxComponent;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
