// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/Components/SecondStageSecondBossComponent.h"

#include "BaseEnemySpawnerForSecondBoss.h"
#include "HealthComponent.h"
#include "SecondBossEnemy.h"
#include "SecondBossEnemyAIController.h"
#include "Player/PlayerCharacter.h"

USecondStageSecondBossComponent::USecondStageSecondBossComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USecondStageSecondBossComponent::BeginPlay()
{
	Super::BeginPlay();
	SecondBoss = Cast<ASecondBossEnemy>(GetOwner());
}

void USecondStageSecondBossComponent::SecondStageStartAction()
{
	if(SecondBoss && GetWorld())
	{
		SecondBoss->StunEnemy(StunTime);
		const auto SecondBossStunTime = GetWorld()->GetTimerManager().GetTimerRemaining(SecondBoss->GetStunTimerHandle());
		
		GetWorld()->GetTimerManager().SetTimer(StunTimer,this,&USecondStageSecondBossComponent::EndSecondStage,SecondBossStunTime);
	}
	EnemiesInBattle.Empty();
	SecondStageAction();
}

void USecondStageSecondBossComponent::SecondStageAction()
{
	if(!ActionTimer.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(ActionTimer,this,&USecondStageSecondBossComponent::SecondStageAction,ActionTime,true);	
	}
	for (const auto EnemySpawner: EnemiesSpawners)
	{
		if(EnemySpawner)
		{
			EnemySpawner->SpawnEnemies();
			EnemySpawner->OnSpawn.AddUObject(this,&USecondStageSecondBossComponent::AddEnemies);
		}
	}
	
	if(!CheckEnemiesTimer.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(CheckEnemiesTimer,this,&USecondStageSecondBossComponent::CheckEnemies,TimeForCheckEnemies,true);
	}
}

void USecondStageSecondBossComponent::CheckEnemies()
{
	TArray<TPair<ABaseEnemy*, float>> Distances;

	for (ABaseEnemy*& Actor : EnemiesInBattle)
	{
		if(SecondBoss->GetControllerSecondBoss()->GetPlayerCharacter())
		{
			float Distance = CalculateDistanceBetweenActors(SecondBoss->GetControllerSecondBoss()->GetPlayerCharacter(), Actor);	
			Distances.Emplace(Actor, Distance);
		}
	}

	Distances.Sort([](const TPair<AActor*, float>& A, const TPair<AActor*, float>& B)
	{
		return A.Value < B.Value;
	});

	TArray<AActor*> NearestActors;
	for (int32 i = 0; i < 3 && i < Distances.Num(); ++i)
	{
		NearestActors.Add(Distances[i].Key);
	}

	int32 CountEnemies = CurrentHowManyEnemiesCanBeInFront;
	
	for (const auto& Dist : Distances)
	{
		if(Dist.Value<=30.0f)
		{
			Dist.Key->SetCanAttack(true);
			continue;
		}
		if(CountEnemies!=0 && !Dist.Key->GetIsTakenDamage())
		{
			Dist.Key->SetCanAttack(true);	
			CountEnemies--;
		}
		else
		{
			Dist.Key->SetCanAttack(false);
		}
	}
}

void USecondStageSecondBossComponent::AddEnemies(ABaseEnemy* Enemy)
{
	if(Enemy)
	{
		EnemiesInBattle.Add(Enemy);
		Enemy->GetHealthComponent()->OnDeath.AddUObject(this,&USecondStageSecondBossComponent::DeleteEnemy);
	}
}

void USecondStageSecondBossComponent::DeleteEnemy(ABaseCharacter* Character)
{
	if(const auto Enemy =  Cast<ABaseEnemy>(Character))
	{
		EnemiesInBattle.Remove(Enemy);	
	}
}

void USecondStageSecondBossComponent::EndSecondStage()
{
	for (const auto& Enemy:EnemiesInBattle)
	{
		Enemy->Death(nullptr);
		Enemy->Destroy();
	}
	if(GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(ActionTimer);
		GetWorld()->GetTimerManager().ClearTimer(StunTimer);
	}
	SecondBoss->EndStage();
}


