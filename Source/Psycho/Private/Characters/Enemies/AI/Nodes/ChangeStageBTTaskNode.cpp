// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/AI/Nodes/ChangeStageBTTaskNode.h"

#include "AIController.h"
#include "SecondBossEnemy.h"

UChangeStageBTTaskNode::UChangeStageBTTaskNode()
{
	NodeName="ChangeStage";
}

EBTNodeResult::Type UChangeStageBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if(!Controller) return EBTNodeResult::Failed;
                   	
	const auto Pawn = Controller->GetPawn();
	if(!Pawn) return EBTNodeResult::Failed;
                   
	if(const auto Enemy = Cast<ASecondBossEnemy>(Pawn))
	{
		Enemy->ChangeStage(NewStage);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
