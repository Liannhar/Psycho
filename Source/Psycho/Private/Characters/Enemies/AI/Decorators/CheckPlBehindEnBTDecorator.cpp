// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/AI/Decorators/CheckPlBehindEnBTDecorator.h"

#include "AIController.h"
#include "FirstBossEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Player/PlayerCharacter.h"

UCheckPlBehindEnBTDecorator::UCheckPlBehindEnBTDecorator()
{
	NodeName="Check Player Behind Enemy";
}

bool UCheckPlBehindEnBTDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto BlackBoard = OwnerComp.GetBlackboardComponent();
	const auto PlayerObject = BlackBoard->GetValueAsObject(PlayerKey.SelectedKeyName);
	const auto Player = Cast<APlayerCharacter>(PlayerObject);
	if(!Player) return false;
	
	const auto Controller = OwnerComp.GetAIOwner();
	if(!Controller) return false;
                   	
	const auto Pawn = Controller->GetPawn();
	if(!Pawn) return false;

	const auto Enemy = Cast<ABaseEnemy>(Pawn);
	if(!Enemy) return false;
	
	return CheckPlayerBehindEnemy(Enemy,Player);
}

bool UCheckPlBehindEnBTDecorator::CheckPlayerBehindEnemy(const AActor* Enemy, const AActor* Player)
{
	const FVector EnemyLocation = Enemy->GetActorLocation();
	const FVector PlayerLocation = Player->GetActorLocation();

	const FRotator EnemyRotation = Enemy->GetActorRotation();
	const FVector EnemyForwardVector = EnemyRotation.Vector();
	FVector VectorToPlayer = PlayerLocation - EnemyLocation;
	VectorToPlayer.Normalize();

	if (FVector::DotProduct(EnemyForwardVector, VectorToPlayer) < 0)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}


