// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoreTypes.h"
#include "Psycho/CoreTypes.h"
#include "StartFightActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDoorOpen, bool, IsOpen);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBossFightStarted, ABaseEnemy*, BossCharacter);

class APsychoGameModeBase;
class ABaseEnemy;
class AEnemySpawner;
class UBoxComponent;
struct FWaves;
class ABaseTriggerBox;

UCLASS()
class PSYCHO_API AStartFightActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AStartFightActor();

	void CheckEnemySpawners();
	void ChangeNeedTrigger(bool NewBool){NeedTrigger=NewBool;}

	void AddStartEnemies(ABaseEnemy* NewStartEnemy);
	
	virtual void ActionStartFightActor(AActor*& OtherActor);
protected:
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	void EndFight();
	bool FightWasStarted = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemies")
	TArray<FWaves> Waves;

	UPROPERTY(EditAnywhere,Category="Collision")
	UBoxComponent* BoxComponent;

	int32 CurrentIndexEnemySpawner = 0;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Enemies")
	TArray<ABaseEnemy*> StartEnemies;

	FTimerHandle CheckEnemiesTimer;
	float TimeForCheckEnemies = 0.5f;
	void CheckEnemies() const;
	UPROPERTY()
	APsychoGameModeBase* CurrentGameMode;
	UPROPERTY()
	AActor* PlayerActor;

  	int32 CurrentHowManyEnemiesCanBeInFront = 2;

	UPROPERTY(BlueprintAssignable)
	FOnDoorOpen OpenDoor;

	UPROPERTY(BlueprintAssignable)
	FBossFightStarted OnBossFightStarted;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Trigger")
	bool NeedTrigger=false;

	
};
