// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ChangeStageBTTaskNode.generated.h"

enum ESecondBossStages : int;
/**
 * 
 */
UCLASS()
class PSYCHO_API UChangeStageBTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()

	UChangeStageBTTaskNode();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere,Category="SecondBoss")
	TEnumAsByte<ESecondBossStages> NewStage;
};
