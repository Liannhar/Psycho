// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TentaculiDamage.generated.h"

class USphereComponent;

UCLASS()
class PSYCHO_API ATentaculiDamage : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATentaculiDamage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void NotifyActorBeginOverlap(AActor* OtherActor);
	UPROPERTY(EditAnywhere,Category="Collision")
	USphereComponent* Sphere;
	
	UPROPERTY(EditAnywhere,Category="Damage")
	float Damage=10.0f;
	FTimerHandle DeleteTimer;

	void Delete();
};
