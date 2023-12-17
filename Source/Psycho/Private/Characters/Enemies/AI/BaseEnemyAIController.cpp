// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/AI/BaseEnemyAIController.h"

#include "BaseEnemy.h"
#include "EnemyAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ABaseEnemyAIController::ABaseEnemyAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UEnemyAIPerceptionComponent>("PerceptionComponent");
	SetPerceptionComponent(*AIPerceptionComponent);
}

void ABaseEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if(const auto AICharacter = Cast<ABaseEnemy>(InPawn))
	{
		RunBehaviorTree(AICharacter->BehaviorTreeAsset);
	}
}

void ABaseEnemyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	const auto FocusActor = GetFocusOnActor();
	SetFocus(FocusActor);
}

AActor* ABaseEnemyAIController::GetFocusOnActor() const
{
	if(!GetBlackboardComponent()) return nullptr;
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
