// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/AI/Nodes/ChangeSpeedEnemyBTNode.h"

#include "AIController.h"
#include "BaseEnemy.h"

UChangeSpeedEnemyBTNode::UChangeSpeedEnemyBTNode()
{
	NodeName="Change MaxWalkSpeed";
}

EBTNodeResult::Type UChangeSpeedEnemyBTNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if(!Controller) return EBTNodeResult::Failed;
                   	
	const auto Pawn = Controller->GetPawn();
	if(!Pawn) return EBTNodeResult::Failed;
                   
	if(const auto Enemy = Cast<ABaseEnemy>(Pawn))
	{
		Enemy->ChangeMaxSpeed(NewSpeed);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
