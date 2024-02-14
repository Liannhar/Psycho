// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/AI/FirstBossAIController.h"

#include "FirstBossEnemy.h"

bool AFirstBossAIController::GetCanFocus() const
{
	if(const auto Enemy = Cast<AFirstBossEnemy>(GetPawn()))
	{
		return Enemy->GetNotIsAttackingNow() && Enemy->GetCurrentStamina()!=0;
	}
	return false;
}
