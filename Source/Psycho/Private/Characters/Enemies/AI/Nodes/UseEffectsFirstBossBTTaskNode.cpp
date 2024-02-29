// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/AI/Nodes/UseEffectsFirstBossBTTaskNode.h"

#include "AIController.h"
#include "BaseEnemy.h"
#include "FirstBossEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"

UUseEffectsFirstBossBTTaskNode::UUseEffectsFirstBossBTTaskNode()
{
	NodeName="Use Effect";
}

EBTNodeResult::Type UUseEffectsFirstBossBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if(!Controller) return EBTNodeResult::Failed;
                   	
	const auto Pawn = Controller->GetPawn();
	if(!Pawn) return EBTNodeResult::Failed;

	if(const auto Enemy = Cast<AFirstBossEnemy>(Pawn))
	{
		Enemy->StartEffectMoving(StaminaCost);
		
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Succeeded;
}
