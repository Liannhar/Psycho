// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PillsDataStructure.generated.h"

/**
 * 
 */
UCLASS()
class PSYCHO_API UPillsDataStructure : public UPrimaryDataAsset
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FString PillName;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UBasePills> PillType;

	FPrimaryAssetId GetPrimaryAssetId() const override { return FPrimaryAssetId("AssetItems", GetFName()); }
public:
	FString* GetPillName() { return &PillName; };
	UStaticMesh* GetMesh() { return Mesh; };
	UTexture2D* GetIcon() { return Icon; };
	TSubclassOf<class UBasePills> GetPillType() { return PillType; };
};
