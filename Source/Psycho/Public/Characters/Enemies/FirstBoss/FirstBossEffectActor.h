// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FirstBossEffectActor.generated.h"

class UPoseableMeshComponent;

UCLASS()
class PSYCHO_API AFirstBossEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AFirstBossEffectActor();


	void Create(USkeletalMeshComponent* NewSkeletalMeshComponent,USkeletalMesh* NewSkeletalMesh);
protected:
	virtual void BeginPlay() override;

	void EndLive();
	
	UPROPERTY()
	UPoseableMeshComponent* PoseableMeshComponent;

	UPROPERTY(EditAnywhere,Category="Mesh")
	UMaterialInterface* NewMaterial;

	FTimerHandle LiveTimerHandle;

	UPROPERTY(EditAnywhere,Category="Live")
	float LiveTime=2.0f;
};
