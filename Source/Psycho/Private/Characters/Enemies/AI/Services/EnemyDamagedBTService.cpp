// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyDamagedBTService.h"

#include "AIController.h"
#include "BaseEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/EnemyAIPerceptionComponent.h"

UEnemyDamagedBTService::UEnemyDamagedBTService()
{
	NodeName="IsEnemyDamaged";
}

void UEnemyDamagedBTService::CanBeDamaged()
{
	GetWorld()->GetTimerManager().ClearTimer(ProbabilityTimerHandle);
}

void UEnemyDamagedBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto BlackBoard = OwnerComp.GetBlackboardComponent();
	if(!BlackBoard) return;
	if(!GetWorld()) return;
	
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Enemy = Cast<ABaseEnemy>(Controller->GetPawn());
	if (!Enemy) return;
	
	const auto PerceptionComponentClass = Controller->GetComponentByClass(UEnemyAIPerceptionComponent::StaticClass());
	if(const auto PerceptionComponent = Cast<UEnemyAIPerceptionComponent>(PerceptionComponentClass))
	{
		const auto EnemyIsNotDamaged = PerceptionComponent->GetEnemyIsNotDamaged();
		if(EnemyIsNotDamaged)
		{
			BlackBoard->SetValueAsBool(EnemyIsDamagedKey.SelectedKeyName,true);
		}
		else
		{
			if(!ProbabilityTimerHandle.IsValid())
			{
				const float RandomNumber = FMath::FRandRange(0.0f, 1.0f);
				if(RandomNumber>Probability)
				{
					GetWorld()->GetTimerManager().SetTimer(ProbabilityTimerHandle,this,&UEnemyDamagedBTService::CanBeDamaged,TimePerBlock);
					Enemy->BlockAttack(); 
					BlackBoard->SetValueAsBool(EnemyIsDamagedKey.SelectedKeyName,true);	
				}
				else
				{
					Enemy->GetDamage();
					BlackBoard->SetValueAsBool(EnemyIsDamagedKey.SelectedKeyName,false);
				}	
			}
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
