// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "TentaculiActor.generated.h"

class ATentaculiDamage;
class APlayerCharacter;
class UNiagaraComponent;

UCLASS()
class PSYCHO_API ATentaculiActor : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATentaculiActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tentaculi")

	UNiagaraComponent* NiagaraComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	APlayerCharacter* Player;
	
	void SpawnSphers();

	FVector CurrentLocation;

	UPROPERTY()
	TArray<ATentaculiDamage*> TentaculiDamageActors;

	FTimerHandle SpawnTimer;
	void OverlapActor(AActor* InOwner);
public:
	void SetPlayer(APlayerCharacter*& NewPlayer){Player=NewPlayer;}
};
