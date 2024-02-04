// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/AI/Nodes/StartAttackBTTaskNode.h"

#include "AIController.h"
#include "BaseEnemy.h"

UStartAttackBTTaskNode::UStartAttackBTTaskNode()
{
	NodeName="StartAttack";
}

EBTNodeResult::Type UStartAttackBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if(!Controller) return EBTNodeResult::Failed;
                   	
	const auto Pawn = Controller->GetPawn();
	if(!Pawn) return EBTNodeResult::Failed;
                   
	if(const auto Enemy = Cast<ABaseEnemy>(Pawn))
	{
		Enemy->SetStartAttack();
		Enemy->ChangeMaxSpeed(Enemy->GetBaseSpeed());
	}
	return EBTNodeResult::Succeeded;
}
