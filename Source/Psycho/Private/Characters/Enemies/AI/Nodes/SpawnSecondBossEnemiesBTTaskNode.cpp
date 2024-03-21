// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/AI/Nodes/SpawnSecondBossEnemiesBTTaskNode.h"

#include "AIController.h"
#include "BaseEnemy.h"
#include "SecondBossEnemy.h"

USpawnSecondBossEnemiesBTTaskNode::USpawnSecondBossEnemiesBTTaskNode()
{
	NodeName="SpawnSecondBoss";
}

EBTNodeResult::Type USpawnSecondBossEnemiesBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if(!Controller) return EBTNodeResult::Failed;
                   	
	const auto Pawn = Controller->GetPawn();
	if(!Pawn) return EBTNodeResult::Failed;
                   
	if(const auto Enemy = Cast<ASecondBossEnemy>(Pawn))
	{
		Enemy->SpawnEnemies(EnemiesCount);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
