// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FirstStageSecondBossComponent.h"
#include "NiagaraComponent.h"
#include "SecondStageSecondBossComponent.h"
#include "Characters/Enemies/BaseEnemy.h"
#include "SecondBossEnemy.generated.h"

class ASecondBossBaseEnemyVersion;
class ABlockingVolume;
class ABaseEnemySpawnerForSecondBoss;
class ASecondBossEnemyAIController;
class UThirdStageSecondBossComponent;
class USecondStageSecondBossComponent;
class UFirstStageSecondBossComponent;
class ASwitchLightActor;
class APointLight;
/**
 * 
 */
UCLASS()
class PSYCHO_API ASecondBossEnemy : public ABaseEnemy
{
	GENERATED_BODY()
public:
	ASecondBossEnemy();

protected:

	UPROPERTY(EditAnywhere,Category="SmokeNiagara")
	UNiagaraComponent* SmokeNiagaraComponent;

	UPROPERTY(EditAnywhere,Category="FirstStage")
	UFirstStageSecondBossComponent* FirstStageSecondBossComponent;
	UPROPERTY(EditAnywhere,Category="SecondStage")
	USecondStageSecondBossComponent* SecondStageSecondBossComponent;
	UPROPERTY(EditAnywhere,Category="ThirdStage")
	UThirdStageSecondBossComponent* ThirdStageSecondBossComponent;
	
	virtual void BeginPlay() override;
	
	ESecondBossStages NextStage;
	void ChangeStage(const ESecondBossStages& CurrentStage);

	UPROPERTY()
	ASecondBossEnemyAIController* SecondBossEnemyAIController;

	UPROPERTY(EditAnywhere,Category="Scream")
	UNiagaraSystem* ScreamNiagara;
	UPROPERTY(EditAnywhere,Category="Scream")
	UAnimMontage* ScreamMontage;
	UPROPERTY(EditAnywhere,Category="Scream")
	float ScreamRadius=300.0f;
	bool bScreamAttack=false;
	FTimerHandle ScreamTimer;
	void EndScreamAttack();
	void ScreamLogic();

	UPROPERTY(EditAnywhere,CAtegory="Circle")
	ABlockingVolume* BlockCylinder;
	TArray<ASecondBossBaseEnemyVersion*> SpawnedEnemies;
	void DeleteEnemy(ABaseCharacter* BaseCharacter);
	void SpawnOneEnemy();
	TArray<FVector> LocationsAroundPlayer();
	FTimerHandle SpawnTimer;
	int32 CurrentEnemyCount=0;
	int32 MaxCountEnemies=0;
	FVector PlayerLocation;
	
public:

	void SetSwitchLightActors(const TArray<ASwitchLightActor*>& NewSwitchLightActors) const { FirstStageSecondBossComponent->SetSwitchLightActors(NewSwitchLightActors);}
	void SetPointsLightsOnLevel(const TArray<APointLight*>& NewPointsLights) const { FirstStageSecondBossComponent->SetPointsLightsOnLevel(NewPointsLights);}
	void SetBaseEnemiesSpawners(const TArray<ABaseEnemySpawnerForSecondBoss*>& EnemiesSpawners) const {SecondStageSecondBossComponent->SetEnemiesSpawners(EnemiesSpawners);}

	void ChangeNiagaraVisibility(const bool&& NewBool) const{ SmokeNiagaraComponent->SetVisibility(NewBool);}

	void ChangeInvulnerable(const bool&& NewBool);

	void EndStage();
	void StartBoss();

	ASecondBossEnemyAIController* GetControllerSecondBoss() const {return SecondBossEnemyAIController;}

	void ScreamAttack();
	bool GetScreamAttack() const {return bScreamAttack;}

	void CircleAction(const int32& CountEnemies);
	void SpawnEnemies(const int32& CountEnemies);
};
