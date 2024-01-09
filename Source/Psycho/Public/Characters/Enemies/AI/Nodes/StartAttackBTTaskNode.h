// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "StartAttackBTTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class PSYCHO_API UStartAttackBTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UStartAttackBTTaskNode();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
