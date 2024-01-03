// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTNode.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AttackEnemyBTNode.generated.h"

/**
 * 
 */
UCLASS()
class PSYCHO_API UAttackEnemyBTNode : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UAttackEnemyBTNode();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
