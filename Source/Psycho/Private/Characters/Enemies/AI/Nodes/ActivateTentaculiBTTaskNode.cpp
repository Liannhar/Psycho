// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/AI/Nodes/ActivateTentaculiBTTaskNode.h"

#include "AIController.h"
#include "SecondBossEnemy.h"

UActivateTentaculiBTTaskNode::UActivateTentaculiBTTaskNode()
{
	NodeName="ActivateTentaculi";
}

EBTNodeResult::Type UActivateTentaculiBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if(!Controller) return EBTNodeResult::Failed;
                   	
	const auto Pawn = Controller->GetPawn();
	if(!Pawn) return EBTNodeResult::Failed;
                   
	if(const auto Enemy = Cast<ASecondBossEnemy>(Pawn))
	{
		Enemy->ActivateTentaculis();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
