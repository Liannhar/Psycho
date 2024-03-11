// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ChangeBoolBTTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class PSYCHO_API UChangeBoolBTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UChangeBoolBTTaskNode();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	FBlackboardKeySelector Key;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	bool NewBool=false;
};
