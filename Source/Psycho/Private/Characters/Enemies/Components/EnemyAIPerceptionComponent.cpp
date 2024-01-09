// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/EnemyAIPerceptionComponent.h"

#include "BaseEnemy.h"
#include "BaseEnemyAIController.h"
#include "Perception/AISense_Damage.h"
#include "Perception/AISense_Sight.h"
#include "Player/PlayerCharacter.h"

AActor* UEnemyAIPerceptionComponent::GetVisiblePlayer() const
{
	TArray<AActor*> FoundActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(),FoundActors);
	if(FoundActors.Num()==0) return nullptr;
	
	for (const auto Actor:FoundActors)
	{
		//Проверка жив ли Actor 
		const auto Player = Cast<APlayerCharacter>(Actor);
		if(Player) return Player;
	}
	return nullptr;
}

TArray<ABaseEnemy*> UEnemyAIPerceptionComponent::GetVisibleEnemies() const
{
	TArray<AActor*> FoundActors;
	TArray<ABaseEnemy*> Enemies;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(),FoundActors);
	if(FoundActors.Num()==0) return Enemies;
	for (const auto Actor:FoundActors)
	{
		//TODO Проверка жив ли Actor 
		if(const auto Enemy = Cast<ABaseEnemy>(Actor))
		{
			Enemies.Add(Enemy);
		}
	}
	return Enemies;
}

bool UEnemyAIPerceptionComponent::GetEnemyIsNotDamaged()
{
	TArray<AActor*> FoundActors;
	
	const auto Owner=GetOwner();
	if(!Owner) return true;

	const auto Controller = Cast<ABaseEnemyAIController>(Owner);
	if(!Controller) return true;

	const auto Pawn = Controller->GetPawn();
	if(!Pawn) return true;

	const auto CurrentEnemy =Cast<ABaseEnemy>(Pawn);
	if(!CurrentEnemy) return true;
	GetCurrentlyPerceivedActors(UAISense_Damage::StaticClass(),FoundActors);
	//GetCurrentlyPerceivedActors(UAISense_Damage::StaticClass(),FoundActors);
	//GetKnownPerceivedActors(UAISense_Damage::StaticClass(),FoundActors);
	if(FoundActors.Num()==0) return true;
	for(auto const Actor:FoundActors)
	{
		UE_LOG(LogTemp,Display,TEXT("%s"),*Actor->GetName());
		if(Actor->IsA(ABaseEnemy::StaticClass()))
		{
			return false;
		}
	}
	return true;
}
