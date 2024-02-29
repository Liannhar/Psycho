// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/AI/Nodes/SpawnDecalBTTaskNode.h"

#include "AIController.h"
#include "Components/DecalComponent.h"
#include "Engine/DecalActor.h"

USpawnDecalBTTaskNode::USpawnDecalBTTaskNode()
{
}

EBTNodeResult::Type USpawnDecalBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if(!Controller) return EBTNodeResult::Failed;
                   	
	const auto Pawn = Controller->GetPawn();
	if(!Pawn) return EBTNodeResult::Failed;

	if(GetWorld())
	{
		if(ADecalActor* NewDecalActor = GetWorld()->SpawnActor<ADecalActor>(ADecalActor::StaticClass(), Pawn->GetActorLocation(), FRotator(0.0f, 0.0f, 0.0f)))
		{
			if (DecalMaterial)
			{
				NewDecalActor->SetDecalMaterial(DecalMaterial);
			}
			NewDecalActor->GetDecal()->DecalSize = DecalSize;
		}
	}
	
	return EBTNodeResult::Succeeded;
}
