// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/AI/Services/FindPlayerBTService.h"

#include "AIController.h"
#include "EnemyAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UFindPlayerBTService::UFindPlayerBTService()
{
	NodeName="Find Player";
}

void UFindPlayerBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto BlackBoard = OwnerComp.GetBlackboardComponent();
	if(!BlackBoard) return;
	
	const auto Controller = OwnerComp.GetAIOwner();
	const auto PerceptionComponentClass = Controller->GetComponentByClass(UEnemyAIPerceptionComponent::StaticClass());
	if(const auto PerceptionComponent = Cast<UEnemyAIPerceptionComponent>(PerceptionComponentClass))
	{
		const auto Player = PerceptionComponent->GetVisiblePlayer();
		BlackBoard->SetValueAsObject(PlayerActorKey.SelectedKeyName,Player);
		if(Player)
		{
			BlackBoard->SetValueAsVector(PlayerLastLocationKey.SelectedKeyName,Player->GetActorLocation());
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}	