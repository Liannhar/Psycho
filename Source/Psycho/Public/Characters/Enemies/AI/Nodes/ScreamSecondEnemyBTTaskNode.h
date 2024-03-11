// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ScreamSecondEnemyBTTaskNode.generated.h"

class ASecondBossEnemy;
/**
 * 
 */
UCLASS()
class PSYCHO_API UScreamSecondEnemyBTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UScreamSecondEnemyBTTaskNode();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	UPROPERTY()
	ASecondBossEnemy* Enemy=nullptr;
};
