// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/AI/Nodes/EndEffectFirstBossBTTaskNode.h"

#include "AIController.h"
#include "FirstBossEnemy.h"

UEndEffectFirstBossBTTaskNode::UEndEffectFirstBossBTTaskNode()
{
	NodeName="End Effect";
}

EBTNodeResult::Type UEndEffectFirstBossBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if(!Controller) return EBTNodeResult::Failed;
                   	
	const auto Pawn = Controller->GetPawn();
	if(!Pawn) return EBTNodeResult::Failed;

	if(const auto Enemy = Cast<AFirstBossEnemy>(Pawn))
	{
		Enemy->EndEffectMoving();
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Succeeded;
}
