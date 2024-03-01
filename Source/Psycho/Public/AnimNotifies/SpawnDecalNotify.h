// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SpawnDecalNotify.generated.h"

/**
 * 
 */
UCLASS()
class PSYCHO_API USpawnDecalNotify : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	UPROPERTY(EditAnywhere,Category="Decal")
	UMaterialInterface* DecalMaterial;
	UPROPERTY(EditAnywhere,Category="Decal")
	FVector DecalSize;
	UPROPERTY(EditAnywhere,Category="Decal")
	float ChangeLocationPositionForwardDecal=0.0f;
};
