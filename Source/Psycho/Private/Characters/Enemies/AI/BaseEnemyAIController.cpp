// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/AI/BaseEnemyAIController.h"

#include "BaseEnemy.h"
#include "EnemyAIPerceptionComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Psycho/PsychoGameModeBase.h"

ABaseEnemyAIController::ABaseEnemyAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UEnemyAIPerceptionComponent>("PerceptionComponent");
	SetPerceptionComponent(*AIPerceptionComponent);
}

void ABaseEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	const auto World = GetWorld();
	const auto AICharacter = Cast<ABaseEnemy>(InPawn);
	if(AICharacter && World)
	{
		RunBehaviorTree( AICharacter->BehaviorTreeAsset);
		const auto GameModeBase = World->GetAuthGameMode();
		if(const auto PsychoGameModeBase = Cast<APsychoGameModeBase>(GameModeBase))
		{
			PsychoGameModeBase->OnChangeFightStatus.AddUObject(this,&ABaseEnemyAIController::ChangeFightStatus);
		}
	}
}

void ABaseEnemyAIController::ChangeFightStatus(bool NewFightStatus)
{
	if(const auto BlackBoard = GetBlackboardComponent())
	{
		FightStatus=NewFightStatus;
		BlackBoard->SetValueAsBool(FightStatusKeyName,FightStatus);
	}
}

bool ABaseEnemyAIController::GetCanFocus() const
{
	if(const auto BaseEnemy = Cast<ABaseEnemy>(GetPawn()))
	{
		return BaseEnemy->GetNotIsAttackingNow();
	}
	return false;
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
	
	if(GetCanFocus() && FightStatus)
	{
		return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
	}
	return nullptr;
}
