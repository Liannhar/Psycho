// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "StunPlayerBTTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class PSYCHO_API UStunPlayerBTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UStunPlayerBTTaskNode();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	FBlackboardKeySelector PlayerKey;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	float StunTime=0.0f;
};
