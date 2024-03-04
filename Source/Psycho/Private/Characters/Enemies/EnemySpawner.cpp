// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/EnemySpawner.h"

#include "BaseEnemy.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Psycho/PsychoGameModeBase.h"

AEnemySpawner::AEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = false;
	BoxComponent=CreateDefaultSubobject<UBoxComponent>("Box Collision");
	BoxComponent->SetBoxExtent(FVector(100.0f,100.0f,50.0f));
}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemySpawner::ActionWithEnemy(ABaseEnemy* Enemy)
{
}

void AEnemySpawner::SpawnOneEnemy()
{
	if(!GetWorld()) return;
	if(SpawnIndex<Enemies.Num())
	{
		const auto NewLocation = UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(),BoxComponent->GetScaledBoxExtent());
		const auto NewSpawnedEnemy = GetWorld()->SpawnActor<ABaseEnemy>(Enemies[SpawnIndex],NewLocation + FVector(0.0f,0.0f,10.0f),GetActorRotation());
		if(NewSpawnedEnemy)
		{
			const auto GameMode = Cast<APsychoGameModeBase>(GetWorld()->GetAuthGameMode());
			ActionWithEnemy(NewSpawnedEnemy);
			GameMode->ChangeEnemiesCount(NewSpawnedEnemy,true);
			SpawnIndex+=1;
		}
	}
	else
	{
		SpawnIndex=0;
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimeHandle);
		Destroy();
	}
}

void AEnemySpawner::SpawnEnemies()
{
	const auto World = GetWorld();
	if(!World) return;

	
	if(!SpawnTimeHandle.IsValid() && GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(SpawnTimeHandle,this,&AEnemySpawner::SpawnOneEnemy,0.2f,true);
	}
}


