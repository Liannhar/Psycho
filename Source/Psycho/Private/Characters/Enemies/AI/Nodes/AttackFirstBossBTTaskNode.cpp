// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/AI/Nodes/AttackFirstBossBTTaskNode.h"

#include "AIController.h"
#include "FirstBossEnemy.h"

UAttackFirstBossBTTaskNode::UAttackFirstBossBTTaskNode()
{
	NodeName="AttackFirstBoss";
	bNotifyTick = true;
}

uint16 UAttackFirstBossBTTaskNode::GetInstanceMemorySize() const
{
	return sizeof(FAttackAIMemory);
}

EBTNodeResult::Type UAttackFirstBossBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	const auto Controller = OwnerComp.GetAIOwner();
	if(!Controller) return EBTNodeResult::Failed;
                     
	const auto Pawn = Controller->GetPawn();
	if(!Pawn) return EBTNodeResult::Failed;
  
	Enemy = Cast<AFirstBossEnemy>(Pawn);
	if(!Enemy) return EBTNodeResult::Failed;
	
	if(!Enemy->GetNotIsAttackingNow())
	{
		Enemy->PreparationBossBeforeAttack(ComboType,ComboIndex,AttackCount-1,NeedRandom,StaminaCost);
		Enemy->Attack();
		return EBTNodeResult::InProgress;
	}
	return EBTNodeResult::Failed;
}

void UAttackFirstBossBTTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (Enemy && Enemy->GetNotIsAttackingNow())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

