// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTNode.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Psycho/CoreTypes.h"
#include "AttackEnemyBTNode.generated.h"


class ABaseEnemy;

UCLASS()
class PSYCHO_API UAttackEnemyBTNode : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UAttackEnemyBTNode();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	UPROPERTY(EditAnywhere,Category="Attacks")
	int32 AttackCount=0;
	
	UPROPERTY(EditAnywhere,Category="Attacks")
	int32 ComboIndex=0;

	UPROPERTY(EditAnywhere,Category="Attacks")
	TEnumAsByte<EComboInput> ComboType;
	
	UPROPERTY(EditAnywhere,Category="Attacks")
	bool NeedRandom=false;

	UPROPERTY()
	ABaseEnemy* Enemy=nullptr;
};
