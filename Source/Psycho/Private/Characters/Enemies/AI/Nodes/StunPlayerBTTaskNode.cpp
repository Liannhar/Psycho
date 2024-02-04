// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/AI/Nodes/StunPlayerBTTaskNode.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Player/PlayerCharacter.h"

UStunPlayerBTTaskNode::UStunPlayerBTTaskNode()
{
	NodeName="StunPlayer";
}

EBTNodeResult::Type UStunPlayerBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto BlackBoard = OwnerComp.GetBlackboardComponent();
	if(!BlackBoard) return EBTNodeResult::Failed;

	const auto Actor = BlackBoard->GetValueAsObject(PlayerKey.SelectedKeyName);
	const auto Player = Cast<APlayerCharacter>(Actor);
	if(!Player) return EBTNodeResult::Failed;

	Player->StartStunPlayer(StunTime);
	return EBTNodeResult::Succeeded;
}
