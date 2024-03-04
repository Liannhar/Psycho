// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KeyActor.generated.h"

class UBoxComponent;
class ADoorBaseActor;

UCLASS()
class PSYCHO_API AKeyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AKeyActor();
	void SetDoorThatNeedKey(ADoorBaseActor* NewDoorThatNeedKey){DoorThatNeedKey=NewDoorThatNeedKey;}
	void EnablePhysics();
protected:
	
	void DisablePhysics();
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Door")
	ADoorBaseActor* DoorThatNeedKey;
	UPROPERTY(EditAnywhere,Category="Components")
	UBoxComponent* CollisionComponent;
	UPROPERTY(EditAnywhere,Category="Components")
	UStaticMeshComponent* StaticMesh;

	FTimerHandle PhysicsTimer;
	float TimeForFall=2.0f;
};
