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

void AEnemySpawner::SpawnEnemies()
{
	const auto World = GetWorld();
	if(!World) return;
	for(const auto Enemy:Enemies)
	{
		const auto NewLocation = UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(),BoxComponent->GetScaledBoxExtent());
		const auto NewSpawnedEnemy = World->SpawnActor<ABaseEnemy>(Enemy,NewLocation+FVector(0.0f,0.0f,90.0f),GetActorRotation());
		const auto GameMode = Cast<APsychoGameModeBase>(World->GetAuthGameMode());
		GameMode->ChangeEnemiesCount(NewSpawnedEnemy,true);
	}
}


