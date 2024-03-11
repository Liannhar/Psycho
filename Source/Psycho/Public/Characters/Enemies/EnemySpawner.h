// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

class UBoxComponent;
class ABaseEnemy;

UCLASS()
class PSYCHO_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemySpawner();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Enemies")
	TArray<TSubclassOf<ABaseEnemy>> Enemies;
	UPROPERTY(EditAnywhere,Category="Collision")
	UBoxComponent* BoxComponent;

	FTimerHandle SpawnTimeHandle;
	int32 SpawnIndex;

	virtual void ActionWithEnemy(ABaseEnemy*& Enemy);
public:

	virtual void EndSpawned();
	virtual void StartSpawnAction();
	UFUNCTION(BlueprintCallable)
	void SpawnEnemies();
	UFUNCTION(BlueprintCallable)
	void SpawnOneEnemy();
};
