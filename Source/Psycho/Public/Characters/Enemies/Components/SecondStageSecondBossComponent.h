// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "Components/ActorComponent.h"
#include "SecondStageSecondBossComponent.generated.h"


class ABaseCharacter;
class ABaseEnemy;
class ASecondBossEnemy;
class ABaseEnemySpawnerForSecondBoss;
class UBehaviorTree;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PSYCHO_API USecondStageSecondBossComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USecondStageSecondBossComponent();

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="SecondStage")
	UBehaviorTree* SecondStageBehaviorTreeAsset;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="SecondStage")
	float ActionTime=2.0f;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="SecondStage")
	float StunTime=10.0f;
	int32 CurrentHowManyEnemiesCanBeInFront=3;
	float TimeForCheckEnemies;

private:
	UPROPERTY()
	TArray<ABaseEnemySpawnerForSecondBoss*> EnemiesSpawners;
	UPROPERTY()
	ASecondBossEnemy* SecondBoss;

	FTimerHandle StunTimer;
	FTimerHandle ActionTimer;
	FTimerHandle CheckEnemiesTimer;

	void CheckEnemies();
	void AddEnemies(ABaseEnemy* Enemy);
	void DeleteEnemy(ABaseCharacter* Character);

	UPROPERTY()
	TArray<ABaseEnemy*> EnemiesInBattle; 

	
	void SecondStageAction();
public:
	UBehaviorTree* GetBehaviorTree() const {return SecondStageBehaviorTreeAsset;}
	void SecondStageStartAction();
	void EndSecondStage();
	void SetEnemiesSpawners(const TArray<ABaseEnemySpawnerForSecondBoss*>& NewEnemiesSpawners){EnemiesSpawners=NewEnemiesSpawners;}
};
