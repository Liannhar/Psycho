// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ActivateTentaculiBTTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class PSYCHO_API UActivateTentaculiBTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()

	UActivateTentaculiBTTaskNode();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
