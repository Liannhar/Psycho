// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/AI/FirstBossAIController.h"

#include "FirstBossEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Player/PlayerCharacter.h"
#include "Psycho/PsychoGameModeBase.h"

void AFirstBossAIController::SetBoolCurrentStamina(const int32 CurrentStamina)
{
	const auto BlackBoard = GetBlackboardComponent();
	if(!BlackBoard) return;
			
	BlackBoard->SetValueAsBool(IsStaminaNotOut,CurrentStamina != 0);
}

bool AFirstBossAIController::GetCanFocus() const
{
	if(const auto Enemy = Cast<AFirstBossEnemy>(GetPawn()))
	{
		return Enemy->GetNotIsAttackingNow() && Enemy->GetCurrentStamina()!=0;
	}
	return false;
}

void AFirstBossAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if(const auto AICharacter = Cast<ABaseEnemy>(InPawn))
	{
		RunBehaviorTree( AICharacter->BehaviorTreeAsset);
		const auto BlackBoard = GetBlackboardComponent();
		if(!BlackBoard) return;
			
		BlackBoard->SetValueAsBool(IsStaminaNotOut,true);
	}
}
