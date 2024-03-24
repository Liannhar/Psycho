// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/AI/Nodes/AttackEnemyBTNode.h"
#include "AIController.h"
#include "BaseEnemy.h"

UAttackEnemyBTNode::UAttackEnemyBTNode()
{
	NodeName="Attack";
	bNotifyTick=true;
}

EBTNodeResult::Type UAttackEnemyBTNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if(!Controller) return EBTNodeResult::Failed;
                   	
	const auto Pawn = Controller->GetPawn();
	if(!Pawn) return EBTNodeResult::Failed;

	Enemy = Cast<ABaseEnemy>(Pawn);
	if(Enemy)
	{
		Enemy->PreparationsBeforeTheAttack(ComboType,ComboIndex,AttackCount-1,NeedRandom);
		Enemy->Attack();
		return EBTNodeResult::InProgress;
	}
	return EBTNodeResult::Failed;
}

void UAttackEnemyBTNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (Enemy && Enemy->GetNotIsAttackingNow())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}}
