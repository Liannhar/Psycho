// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlotActor.generated.h"

class UBoxComponent;

UCLASS()
class PSYCHO_API APlotActor : public AActor
{
	GENERATED_BODY()
	
public:	
	APlotActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,Category="Dialogue")
	TArray<USoundWave*> SoundWaves;
	UPROPERTY(EditAnywhere,Category="Dialogue")
	bool NeedOwner=true;
	UPROPERTY(EditAnywhere,Category="Collision")
	UBoxComponent* BoxComponent;

	bool WasOverlap = false;
	int32 CurrentIndex=0;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
public:
	UFUNCTION(BlueprintCallable)
	void PlayDialog(AActor*& NeededOwner);
};
