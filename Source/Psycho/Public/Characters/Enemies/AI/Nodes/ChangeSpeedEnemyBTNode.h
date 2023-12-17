// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTNode.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ChangeSpeedEnemyBTNode.generated.h"

/**
 * Change Max Walk Speed Enemy Class
 */
UCLASS()
class PSYCHO_API UChangeSpeedEnemyBTNode : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UChangeSpeedEnemyBTNode();
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Speed")
    float NewSpeed=100.0f;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
