// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/AI/Decorators/CheckProcentHPBTDecorator.h"

#include "AIController.h"
#include "HealthComponent.h"
#include "SecondBossEnemy.h"

UCheckProcentHPBTDecorator::UCheckProcentHPBTDecorator()
{
	NodeName="Check procent HP";
}

bool UCheckProcentHPBTDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if(!Controller) return false;
                     
	const auto Pawn = Controller->GetPawn();
	if(!Pawn) return false;
  
	const auto Enemy = Cast<ABaseEnemy>(Pawn);
	if(!Enemy) return false;

	const auto CurrentPercentHp =Enemy->GetHealthComponent()->GetPercentHP();

	if(CurrentPercentHp<MaxValue && CurrentPercentHp>=MinValue)
	{
		return true;
	}
	return false;
}
