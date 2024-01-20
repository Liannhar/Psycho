// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StartFightActor.generated.h"

class ABaseEnemy;
class AEnemySpawner;
class UBoxComponent;

UCLASS()
class PSYCHO_API AStartFightActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AStartFightActor();

	void CheckEnemySpawners();
protected:
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	bool FightWasStarted = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Spawners")
	TArray<AEnemySpawner*> EnemySpawners;

	UPROPERTY(EditAnywhere,Category="Collision")
	UBoxComponent* BoxComponent;

	int32 CurrentIndexEnemySpawner = 0;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Spawners")
	bool NeedSpawnInStartOfBattle = true;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Enemies")
	TArray<ABaseEnemy*> StartEnemies;
};
