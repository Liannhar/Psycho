// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/StartFightActor.h"
#include "BaseEnemy.h"
#include "EnemySpawner.h"
#include "CoreTypes.h"
#include "Components/BoxComponent.h"
#include "Player/PlayerCharacter.h"
#include "Psycho/PsychoGameModeBase.h"

AStartFightActor::AStartFightActor()
{
	PrimaryActorTick.bCanEverTick = false;
	BoxComponent=CreateDefaultSubobject<UBoxComponent>("Box Collision");
	BoxComponent->SetBoxExtent(FVector(100.0f,100.0f,50.0f));
}

void AStartFightActor::EndFight()
{
	CurrentGameMode->SetFightStatus(false);
	CurrentGameMode->Player=nullptr;
	OpenDoor.Broadcast(true);
	CurrentGameMode->SetCurrentStartFightActor(nullptr);
	GetWorld()->GetTimerManager().ClearTimer(CheckEnemiesTimer);
	Destroy();
}

void AStartFightActor::BeginPlay()
{
	Super::BeginPlay();
	if(const auto GameMode = Cast<APsychoGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		CurrentGameMode=GameMode;
	}
}



void AStartFightActor::CheckEnemySpawners()
{
	if(CurrentIndexEnemySpawner<Waves.Num())
	{
		CurrentHowManyEnemiesCanBeInFront=Waves[CurrentIndexEnemySpawner].HowManyEnemiesCanBeInFront;
		for (const auto EnemySpawner: Waves[CurrentIndexEnemySpawner].EnemySpawners)
		{
			if(EnemySpawner)
			{
				EnemySpawner->SpawnEnemies();
				CurrentIndexEnemySpawner++;
				CurrentGameMode->SetFightStatus(true);
			}
		}
		return;	
	}
	EndFight();
}

void AStartFightActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if(NeedTrigger)
	{
		return;
	}
	if(Cast<APlayerCharacter>(OtherActor))
	{
		ActionStartFightActor(OtherActor);	
	}
}

void AStartFightActor::CheckEnemies() const
{
	const auto EnemiesInBattle = CurrentGameMode->GetEnemiesInBattle();

	TArray<TPair<ABaseEnemy*, float>> Distances;

	for (ABaseEnemy* Actor : EnemiesInBattle)
	{
		float Distance = CalculateDistance(PlayerActor, Actor);
		Distances.Emplace(Actor, Distance);
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

float AStartFightActor::CalculateDistance(const AActor* Actor1, const ABaseEnemy* Actor2)
{
	const FVector Location1 = Actor1->GetActorLocation();
	const FVector Location2 = Actor2->GetActorLocation();
	return FVector::Dist(Location1, Location2);
}

void AStartFightActor::AddStartEnemies(ABaseEnemy* NewStartEnemy)
{
	if(NewStartEnemy)
	{
		StartEnemies.Add(NewStartEnemy);	
	}
}

void AStartFightActor::ActionStartFightActor(AActor*& OtherActor)
{
	if(!FightWasStarted)
	{
		FightWasStarted=true;
		CurrentGameMode->SetStartEnemies(StartEnemies);
		CurrentGameMode->SetCurrentStartFightActor(this);
		CurrentGameMode->ChangeEnemiesCount(nullptr);
		PlayerActor=OtherActor;
		CurrentGameMode->Player=OtherActor;
		CurrentGameMode->SetFightStatus(true);
		OpenDoor.Broadcast(false);
		GetWorld()->GetTimerManager().SetTimer(CheckEnemiesTimer,this,&AStartFightActor::CheckEnemies,TimeForCheckEnemies,true);
	}
}


