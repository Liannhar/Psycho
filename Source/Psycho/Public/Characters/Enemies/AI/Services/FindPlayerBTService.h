// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FindPlayerBTService.generated.h"

/**
 * Service for finding Player
 */
UCLASS()
class PSYCHO_API UFindPlayerBTService : public UBTService
{
	GENERATED_BODY()
public:
	UFindPlayerBTService();
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	FBlackboardKeySelector PlayerActorKey;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	FBlackboardKeySelector PlayerLastLocationKey;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
