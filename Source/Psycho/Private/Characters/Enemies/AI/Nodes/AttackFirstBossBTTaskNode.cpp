// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/AI/Nodes/AttackFirstBossBTTaskNode.h"

#include "AIController.h"
#include "FirstBossEnemy.h"

UAttackFirstBossBTTaskNode::UAttackFirstBossBTTaskNode()
{
	NodeName="AttackFirstBoss";
}

EBTNodeResult::Type UAttackFirstBossBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if(!Controller) return EBTNodeResult::Failed;
                   	
	const auto Pawn = Controller->GetPawn();
	if(!Pawn) return EBTNodeResult::Failed;
                   
	if(const auto Enemy = Cast<AFirstBossEnemy>(Pawn))
	{
		Enemy->PreparationBossBeforeAttack(ComboType,ComboIndex,AttackCount-1,NeedRandom,StaminaCost);
		Enemy->Attack();
	}
	return EBTNodeResult::Succeeded;
}
