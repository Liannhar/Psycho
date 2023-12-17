// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FindPlayerLastLocationBTService.generated.h"

/**
 * 
 */
UCLASS()
class PSYCHO_API UFindPlayerLastLocationBTService : public UBTService
{
	GENERATED_BODY()
public:
	UFindPlayerLastLocationBTService();
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	FBlackboardKeySelector PlayerLastLocationKey;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
