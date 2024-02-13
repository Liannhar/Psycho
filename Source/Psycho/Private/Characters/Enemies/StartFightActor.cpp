// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/StartFightActor.h"

#include "BaseEnemy.h"
#include "EnemySpawner.h"
#include "Components/BoxComponent.h"
#include "Player/PlayerCharacter.h"
#include "Psycho/PsychoGameModeBase.h"

AStartFightActor::AStartFightActor()
{
	PrimaryActorTick.bCanEverTick = false;
	BoxComponent=CreateDefaultSubobject<UBoxComponent>("Box Collision");
	BoxComponent->SetBoxExtent(FVector(100.0f,100.0f,50.0f));
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

	if(CurrentIndexEnemySpawner<EnemySpawners.Num())
	{
		EnemySpawners[CurrentIndexEnemySpawner]->SpawnEnemies();
		CurrentIndexEnemySpawner++;
		CurrentGameMode->SetFightStatus(true);
		return;
	}
	CurrentGameMode->SetFightStatus(false);
	CurrentGameMode->PLayer=nullptr;
	CurrentGameMode->SetCurrentStartFightActor(nullptr);
	GetWorld()->GetTimerManager().ClearTimer(CheckEnemiesTimer);
	Destroy();
}

void AStartFightActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	const auto PlayerChar= Cast<APlayerCharacter>(OtherActor);
	if(PlayerChar && !FightWasStarted)
	{
		FightWasStarted=true;
		CurrentGameMode->SetStartEnemies(StartEnemies);
		if(NeedSpawnInStartOfBattle)
		{
			CheckEnemySpawners();
		}
		CurrentGameMode->SetCurrentStartFightActor(this);
		CurrentGameMode->SetFightStatus(true);
		PlayerActor=OtherActor;
		CurrentGameMode->PLayer=OtherActor;
		GetWorld()->GetTimerManager().SetTimer(CheckEnemiesTimer,this,&AStartFightActor::CheckEnemies,TimeForCheckEnemies,true);
	}
}

void AStartFightActor::CheckEnemies()
{
	const auto EnemiesInBattle = CurrentGameMode->GetEnemiesInBattle();

	TArray<TPair<ABaseEnemy*, float>> Distances;

	for (auto Actor : EnemiesInBattle)
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

	int32 CountEnemies = HowManyEnemiesInCanBeFront;
	
	for (const auto Dist : Distances)
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


