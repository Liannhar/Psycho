// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemiesAttackBTService.h"

#include "AIController.h"
#include "BaseEnemy.h"
#include "EnemyAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UEnemiesAttackBTService::UEnemiesAttackBTService()
{
	NodeName="Another enemy attacks";
}

void UEnemiesAttackBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto BlackBoard = OwnerComp.GetBlackboardComponent();
	if(!BlackBoard) return;
	const auto Controller = OwnerComp.GetAIOwner();
	const auto PerceptionComponentClass = Controller->GetComponentByClass(UEnemyAIPerceptionComponent::StaticClass());
	if(const auto PerceptionComponent = Cast<UEnemyAIPerceptionComponent>(PerceptionComponentClass))
	{
		bool CanAttack=true;
		auto Enemies = PerceptionComponent->GetVisibleEnemies();
		if (Enemies.Num()>0)
		{
			for (const auto Enemy:Enemies)
			{
				if(Enemy->IsEnemyAttacking())
				{
					CanAttack=false;
					break;
				}
			}
		}
		BlackBoard->SetValueAsBool(EnemyIsAttackingKey.SelectedKeyName,CanAttack);	
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
