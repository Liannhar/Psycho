// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/AI/Nodes/ScreamSecondEnemyBTTaskNode.h"

#include "AIController.h"
#include "SecondBossEnemy.h"

UScreamSecondEnemyBTTaskNode::UScreamSecondEnemyBTTaskNode()
{
	NodeName="ScreamAttackSecondBoss";
	bNotifyTick = true;
}

EBTNodeResult::Type UScreamSecondEnemyBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if(!Controller) return EBTNodeResult::Failed;
                     
	const auto Pawn = Controller->GetPawn();
	if(!Pawn) return EBTNodeResult::Failed;
  
	Enemy = Cast<ASecondBossEnemy>(Pawn);
	if(!Enemy) return EBTNodeResult::Failed;
	
	if(!Enemy->GetScreamAttack())
	{
		Enemy->ScreamAttack();
		return EBTNodeResult::InProgress;
	}
	return EBTNodeResult::Failed;
}

void UScreamSecondEnemyBTTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (Enemy && !Enemy->GetScreamAttack())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
