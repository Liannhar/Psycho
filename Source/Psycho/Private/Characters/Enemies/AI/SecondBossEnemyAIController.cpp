// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/AI/SecondBossEnemyAIController.h"

#include "BaseEnemy.h"

void ASecondBossEnemyAIController::ChangeBTStage()
{
	if(const auto AICharacter = Cast<ABaseEnemy>(GetPawn()) )
	{
		RunBehaviorTree( AICharacter->BehaviorTreeAsset);
	}
}
