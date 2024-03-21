// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FirstStageSecondBossComponent.h"
#include "NiagaraComponent.h"
#include "SecondStageSecondBossComponent.h"
#include "Characters/Enemies/BaseEnemy.h"
#include "SecondBossEnemy.generated.h"

class ATentaculiActor;
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

	UPROPERTY()
	ASecondBossEnemyAIController* SecondBossEnemyAIController;

	UPROPERTY(EditAnywhere,Category="ThirdStage")
	UNiagaraSystem* ScreamNiagara;
	UPROPERTY(EditAnywhere,Category="ThirdStage")
	UAnimMontage* ScreamMontage;
	UPROPERTY(EditAnywhere,Category="ThirdStage")
	float ScreamRadius=150.0f;
	bool bScreamAttack=false;
	FTimerHandle ScreamTimer;
	FTimerHandle EndScreamTimer;
	void EndScreamAttack();
	void ScreamLogic();

	UPROPERTY(EditAnywhere,CAtegory="ThirdStage")
	ABlockingVolume* BlockCylinder;
	TArray<ASecondBossBaseEnemyVersion*> SpawnedEnemies;
	FTimerHandle SpawnTimer;
	int32 CurrentEnemyCount=0;
	int32 MaxCountEnemies=0;
	float SpawnRadiusAroundPlayer=100.f;
	UPROPERTY()
	TArray<FVector> LocationsAroundPlayer;
	UPROPERTY(EditAnywhere,Category="ThirdStage")
	TSubclassOf<ASecondBossBaseEnemyVersion> SecondBossSubClass;
	
	void DeleteEnemy(ABaseCharacter* BaseCharacter);
	void SpawnOneEnemy();
	TArray<FVector> FindLocationsAroundPlayer() const;
	FVector PlayerLocation;

	UPROPERTY()
	TArray<ATentaculiActor*> Tentaculis; 
	FTimerHandle ActiveTimerHandleTentaciuli;
	void DeactivateTentaculis();
	UPROPERTY(EditAnywhere,Category="ThirdStage")
	float TentaculiActiveTime=60.f;
public:

	void SetSwitchLightActors(const TArray<ASwitchLightActor*>& NewSwitchLightActors) const { FirstStageSecondBossComponent->SetSwitchLightActors(NewSwitchLightActors);}
	void SetPointsLightsOnLevel(const TArray<APointLight*>& NewPointsLights) const { FirstStageSecondBossComponent->SetPointsLightsOnLevel(NewPointsLights);}
	void SetBaseEnemiesSpawners(const TArray<ABaseEnemySpawnerForSecondBoss*>& EnemiesSpawners) const {SecondStageSecondBossComponent->SetEnemiesSpawners(EnemiesSpawners);}
	void SetTentaculisActors(const TArray<ATentaculiActor*>& TentaculiActors) {Tentaculis=TentaculiActors;}

	void ChangeNiagaraVisibility(const bool&& NewBool) const{ SmokeNiagaraComponent->SetVisibility(NewBool);}

	void ChangeInvulnerable(const bool&& NewBool) const;
	
	void EndStage();
	void StartBoss();

	ASecondBossEnemyAIController* GetControllerSecondBoss() const {return SecondBossEnemyAIController;}

	void ScreamAttack();
	bool GetIsScreamAttack() const {return bScreamAttack;}

	void CircleAction(const int32& CountEnemies);
	void SpawnEnemies(const int32& CountEnemies);

	void ActivateTentaculis();

	void ChangeStage(const ESecondBossStages& CurrentStage);
};
