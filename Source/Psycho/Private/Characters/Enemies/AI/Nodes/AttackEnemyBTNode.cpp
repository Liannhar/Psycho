// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/AI/Nodes/AttackEnemyBTNode.h"
#include "AIController.h"
#include "BaseEnemy.h"

UAttackEnemyBTNode::UAttackEnemyBTNode()
{
	NodeName="Attack";
}

EBTNodeResult::Type UAttackEnemyBTNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if(!Controller) return EBTNodeResult::Failed;
                   	
	const auto Pawn = Controller->GetPawn();
	if(!Pawn) return EBTNodeResult::Failed;
                   
	if(const auto Enemy = Cast<ABaseEnemy>(Pawn))
	{
		Enemy->ChangeCountCombo(ComboType,ComboIndex,AttackCount-1,NeedRandom);
		Enemy->Attack();
	}
	return EBTNodeResult::Succeeded;
}
