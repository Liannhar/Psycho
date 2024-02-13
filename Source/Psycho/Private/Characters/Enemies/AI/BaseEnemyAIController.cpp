// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/AI/BaseEnemyAIController.h"

#include "BaseEnemy.h"
#include "EnemyAIPerceptionComponent.h"
#include "NavigationSystem.h"
#include "AI/NavigationSystemBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
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

			
			if(PsychoGameModeBase->PLayer)
			{
				BlackBoard->SetValueAsObject(FocusOnKeyName,PsychoGameModeBase->PLayer);
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

void ABaseEnemyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	const auto FocusActor = GetFocusOnActor();
	SetFocus(FocusActor);
}

/*FPathFollowingRequestResult ABaseEnemyAIController::MoveTo(const FAIMoveRequest& MoveRequest,
	FNavPathSharedPtr* OutPath)
{	
	FPathFollowingRequestResult ResultData;
	ResultData.Code = EPathFollowingRequestResult::Failed;

	if (MoveRequest.IsValid() == false)
	{
		return ResultData;
	}

	if (GetPathFollowingComponent() == nullptr)
	{
		return ResultData;
	}

	ensure(MoveRequest.GetNavigationFilter() || !DefaultNavigationFilterClass);

	bool bCanRequestMove = true;
	bool bAlreadyAtGoal = false;
	
	if (!MoveRequest.IsMoveToActorRequest())
	{
		if (MoveRequest.GetGoalLocation().ContainsNaN() || FAISystem::IsValidLocation(MoveRequest.GetGoalLocation()) == false)
		{
			bCanRequestMove = false;
		}

		// fail if projection to navigation is required but it failed
		if (bCanRequestMove && MoveRequest.IsProjectingGoal())
		{
			UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
			const FNavAgentProperties& AgentProps = GetNavAgentPropertiesRef();
			FNavLocation ProjectedLocation;

			if (NavSys && !NavSys->ProjectPointToNavigation(MoveRequest.GetGoalLocation(), ProjectedLocation, INVALID_NAVEXTENT, &AgentProps))
			{
				bCanRequestMove = false;
			}

			MoveRequest.UpdateGoalLocation(ProjectedLocation.Location);
		}

		bAlreadyAtGoal = bCanRequestMove && GetPathFollowingComponent()->HasReached(MoveRequest);
	}
	else 
	{
		bAlreadyAtGoal = bCanRequestMove && GetPathFollowingComponent()->HasReached(MoveRequest);
	}

	if (bAlreadyAtGoal)
	{
		ResultData.MoveId = GetPathFollowingComponent()->RequestMoveWithImmediateFinish(EPathFollowingResult::Success);
		ResultData.Code = EPathFollowingRequestResult::AlreadyAtGoal;
	}
	else if (bCanRequestMove)
	{
		FPathFindingQuery PFQuery;

		const bool bValidQuery = BuildPathfindingQuery(MoveRequest, PFQuery);
		if (bValidQuery)
		{
			FNavPathSharedPtr Path;
			FindPathForMoveRequest(MoveRequest, PFQuery, Path);

			const FAIRequestID RequestID = Path.IsValid() ? RequestMove(MoveRequest, Path) : FAIRequestID::InvalidRequest;
			if (RequestID.IsValid())
			{
				bAllowStrafe = MoveRequest.CanStrafe();
				ResultData.MoveId = RequestID;
				ResultData.Code = EPathFollowingRequestResult::RequestSuccessful;

				if (OutPath)
				{
					*OutPath = Path;
				}
			}
		}
	}

	if (ResultData.Code == EPathFollowingRequestResult::Failed)
	{
		ResultData.MoveId = GetPathFollowingComponent()->RequestMoveWithImmediateFinish(EPathFollowingResult::Invalid);
	}

	return ResultData;
}*/

AActor* ABaseEnemyAIController::GetFocusOnActor() const
{
	if(!GetBlackboardComponent()) return nullptr;
	
	if(GetCanFocus() && FightStatus)
	{
		return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
	}
	return nullptr;
}
