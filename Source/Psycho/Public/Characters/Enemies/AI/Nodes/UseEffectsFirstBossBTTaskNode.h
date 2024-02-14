// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UseEffectsFirstBossBTTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class PSYCHO_API UUseEffectsFirstBossBTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UUseEffectsFirstBossBTTaskNode();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere,Category="Stamina")
	int32 StaminaCost=0;
};
