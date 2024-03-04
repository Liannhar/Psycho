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
	UE_LOG(LogTemp,Display,TEXT("%d"),CurrentAttackEnd?1:0);
	const auto Controller = OwnerComp.GetAIOwner();
	if(!Controller) return EBTNodeResult::Failed;
                   	
	const auto Pawn = Controller->GetPawn();
	if(!Pawn) return EBTNodeResult::Failed;
	
	const auto Enemy = Cast<AFirstBossEnemy>(Pawn);
	
	/*if(Enemy && !Enemy->GetNotIsAttackingNow() && !CurrentAttackEnd)
	{
		CurrentAttackEnd=true;
		return EBTNodeResult::Succeeded;
	}*/

	UE_LOG(LogTemp,Display,TEXT("%d"),CurrentAttackEnd?1:0);
	if(Enemy )
	{
		UE_LOG(LogTemp,Display,TEXT("%d"),CurrentAttackEnd?1:0);
		Enemy->PreparationBossBeforeAttack(ComboType,ComboIndex,AttackCount-1,NeedRandom,StaminaCost);
		Enemy->Attack();
		CurrentAttackEnd=false;
		UE_LOG(LogTemp,Display,TEXT("%d"),CurrentAttackEnd?1:0);
	}
	
	return EBTNodeResult::Succeeded;
}
