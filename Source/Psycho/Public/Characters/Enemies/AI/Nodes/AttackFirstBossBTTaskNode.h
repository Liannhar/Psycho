// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Psycho/CoreTypes.h"
#include "AttackFirstBossBTTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class PSYCHO_API UAttackFirstBossBTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UAttackFirstBossBTTaskNode();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere,Category="Attacks")
	int32 StaminaCost=0;
	
	UPROPERTY(EditAnywhere,Category="Attacks")
	int32 AttackCount=0;
	
	UPROPERTY(EditAnywhere,Category="Attacks")
	int32 ComboIndex=0;

	bool CurrentAttackEnd = true;
	
	UPROPERTY(EditAnywhere,Category="Attacks")
	TEnumAsByte<EComboInput> ComboType;
	
	UPROPERTY(EditAnywhere,Category="Attacks")
	bool NeedRandom=false;
};
