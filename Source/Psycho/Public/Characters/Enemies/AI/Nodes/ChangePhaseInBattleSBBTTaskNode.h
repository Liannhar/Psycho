// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ChangePhaseInBattleSBBTTaskNode.generated.h"

class ASecondBossEnemy;
/**
 * 
 */
UCLASS()
class PSYCHO_API UChangePhaseInBattleSbbtTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UChangePhaseInBattleSbbtTaskNode();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	UPROPERTY()
	ASecondBossEnemy* Enemy=nullptr;

	UPROPERTY(EditAnywhere,Category="Rounds")
	UBehaviorTree* FirstRoundBehaviorTreeAsset;
	UPROPERTY(EditAnywhere,Category="Rounds")
	UBehaviorTree* SecondRoundBehaviorTreeAsset;
	UPROPERTY(EditAnywhere,Category="Rounds")
	UBehaviorTree* ThirdRoundBehaviorTreeAsset;
};
