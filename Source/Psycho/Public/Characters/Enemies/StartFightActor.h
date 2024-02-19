// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StartFightActor.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDoorOpen,bool,IsOpen);


class APsychoGameModeBase;
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
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Enemies")
	TArray<AEnemySpawner*> EnemySpawners;

	UPROPERTY(EditAnywhere,Category="Collision")
	UBoxComponent* BoxComponent;

	int32 CurrentIndexEnemySpawner = 0;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Enemies")
	bool NeedSpawnInStartOfBattle = true;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Enemies")
	TArray<ABaseEnemy*> StartEnemies;



	FTimerHandle CheckEnemiesTimer;
	float TimeForCheckEnemies = 0.5f;
	void CheckEnemies();
	float CalculateDistance(const AActor* Actor1, const ABaseEnemy* Actor2);
	UPROPERTY()
	APsychoGameModeBase* CurrentGameMode;
	UPROPERTY()
	AActor* PlayerActor;

	UPROPERTY(EditAnywhere,Category="Enemies")
	int32 HowManyEnemiesInCanBeFront = 2;

	UPROPERTY(BlueprintAssignable)
	FOnDoorOpen OpenDoor;
};
