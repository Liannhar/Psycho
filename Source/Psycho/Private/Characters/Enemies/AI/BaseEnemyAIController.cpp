// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/AI/BaseEnemyAIController.h"

#include "BaseEnemy.h"
#include "EnemyAIPerceptionComponent.h"
#include "NavigationSystem.h"
#include "AI/NavigationSystemBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Player/PlayerCharacter.h"
#include "Psycho/PsychoGameModeBase.h"

class UNavigationSystemV1;

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
			ChangeFightStatus(PsychoGameModeBase->GetFightStatus());
			PsychoGameModeBase->OnChangeFightStatus.AddUObject(this,&ABaseEnemyAIController::ChangeFightStatus);
			const auto BlackBoard = GetBlackboardComponent();
			if(!BlackBoard) return;
			
			BlackBoard->SetValueAsBool(IsPawnNotDamaged,true);
			BlackBoard->SetValueAsBool(IsPawnCanAttack,false);

			
			if(PsychoGameModeBase->Player)
			{
				PlayerCharacter = Cast<APlayerCharacter>(PsychoGameModeBase->Player);
				BlackBoard->SetValueAsObject(FocusOnKeyName,PsychoGameModeBase->Player);
			}
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

void ABaseEnemyAIController::ChangeIsPawnDamage(bool NewBool)
{
	if(const auto BlackBoard = GetBlackboardComponent())
	{
		BlackBoard->SetValueAsBool(IsPawnNotDamaged,NewBool);
	}
}

void ABaseEnemyAIController::ChangeIsPawnCanAttack(bool NewBool)
{
	if(const auto BlackBoard = GetBlackboardComponent())
	{
		BlackBoard->SetValueAsBool(IsPawnCanAttack,NewBool);
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

AActor* ABaseEnemyAIController::GetFocusOnActor() const
{
	if(!GetBlackboardComponent()) return nullptr;
	
	if(GetCanFocus() && FightStatus)
	{
		return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
	}
	return nullptr;
}

void ABaseEnemyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	const auto FocusActor = GetFocusOnActor();
	SetFocus(FocusActor);
}
