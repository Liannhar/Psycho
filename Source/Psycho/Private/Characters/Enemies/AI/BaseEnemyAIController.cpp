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
			FightStatus=PsychoGameModeBase->GetFightStatus();
			PsychoGameModeBase->OnChangeFightStatus.AddUObject(this,&ABaseEnemyAIController::ChangeFightStatus);

			const auto BlackBoard = GetBlackboardComponent();
			if(!BlackBoard) return;
			BlackBoard->SetValueAsBool(IsPawnNotDamagedKeyName,true);
			BlackBoard->SetValueAsBool(IsPawnCanAttackKeyName,false);
			BlackBoard->SetValueAsBool(FightStatusKeyName,FightStatus);
			
			if(PsychoGameModeBase->Player)
			{
				PlayerCharacter = Cast<APlayerCharacter>(PsychoGameModeBase->Player);
				BlackBoard->SetValueAsObject(FocusOnKeyName,PsychoGameModeBase->Player);
			}

		}
		
	}
}

void ABaseEnemyAIController::ChangeFightStatus(const bool NewFightStatus)
{
	const auto GameModeBase = GetWorld()->GetAuthGameMode();
	if(const auto PsychoGameModeBase = Cast<APsychoGameModeBase>(GameModeBase))
	{
		PlayerCharacter = Cast<APlayerCharacter>(PsychoGameModeBase->Player);
		
		const auto BlackBoard = GetBlackboardComponent();
		if(!BlackBoard) return;

		BlackBoard->SetValueAsObject(FocusOnKeyName,PlayerCharacter);

		FightStatus=NewFightStatus;
		BlackBoard->SetValueAsBool(FightStatusKeyName,FightStatus);
	}
}

AActor* ABaseEnemyAIController::GetPlayerActor() const
{
	if(!GetBlackboardComponent()) return nullptr;
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}

void ABaseEnemyAIController::ChangeIsPawnDamage(const bool& NewBool)
{
	if(const auto BlackBoard = GetBlackboardComponent())
	{
		BlackBoard->SetValueAsBool(IsPawnNotDamagedKeyName,NewBool);
	}
}

void ABaseEnemyAIController::ChangeIsPawnCanAttack(const bool& NewBool)
{
	if(const auto BlackBoard = GetBlackboardComponent())
	{
		BlackBoard->SetValueAsBool(IsPawnCanAttackKeyName,NewBool);
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
	
	if(GetCanFocus() && FightStatus)
	{
		return GetPlayerActor();
	}
	return nullptr;
}

void ABaseEnemyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	const auto FocusActor = GetFocusOnActor();
	SetFocus(FocusActor);
}
