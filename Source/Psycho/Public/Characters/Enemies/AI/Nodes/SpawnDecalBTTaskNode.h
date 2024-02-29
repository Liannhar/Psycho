// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SpawnDecalBTTaskNode.generated.h"

class ADecalActor;

UCLASS()
class PSYCHO_API USpawnDecalBTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
public:
	USpawnDecalBTTaskNode();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	UPROPERTY(EditAnywhere,Category="Decal")
	UMaterialInterface* DecalMaterial;
	UPROPERTY(EditAnywhere,Category="Decal")
	FVector DecalSize;
};
