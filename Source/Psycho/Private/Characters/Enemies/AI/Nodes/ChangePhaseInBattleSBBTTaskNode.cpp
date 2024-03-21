// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/AI/Nodes/ChangePhaseInBattleSBBTTaskNode.h"

#include "AIController.h"
#include "HealthComponent.h"
#include "SecondBossEnemy.h"

UChangePhaseInBattleSbbtTaskNode::UChangePhaseInBattleSbbtTaskNode()
{
	NodeName="ChangePhaseSecondBossBattle";
}

EBTNodeResult::Type UChangePhaseInBattleSbbtTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if(!Controller) return EBTNodeResult::Failed;
                     
	const auto Pawn = Controller->GetPawn();
	if(!Pawn) return EBTNodeResult::Failed;
  
	Enemy = Cast<ASecondBossEnemy>(Pawn);
	if(!Enemy) return EBTNodeResult::Failed;

	const auto CurrentPercentHp =Enemy->GetHealthComponent()->GetPercentHP();
	
	if(CurrentPercentHp>=0.8f && FirstRoundBehaviorTreeAsset)
	{
		Enemy->ChangeBehaviorTreeAsset(FirstRoundBehaviorTreeAsset);
		return EBTNodeResult::Succeeded;
	}
	if (CurrentPercentHp<0.8f && CurrentPercentHp>=0.4f && SecondRoundBehaviorTreeAsset)
	{
		Enemy->ChangeBehaviorTreeAsset(SecondRoundBehaviorTreeAsset);
		return EBTNodeResult::Succeeded;

	}
	if(CurrentPercentHp<0.4f && ThirdRoundBehaviorTreeAsset)
	{
		Enemy->ChangeBehaviorTreeAsset(ThirdRoundBehaviorTreeAsset);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
