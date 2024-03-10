// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FirstStageSecondBossComponent.h"
#include "NiagaraComponent.h"
#include "Characters/Enemies/BaseEnemy.h"
#include "SecondBossEnemy.generated.h"

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

	void SecondStageAction();
	void ThirdStageAction();
	void ChangeStage(const ESecondBossStages& CurrentStage);
	
	virtual void BeginPlay() override;
	
	ESecondBossStages CurrentStage;

	UPROPERTY()
	ASecondBossEnemyAIController* SecondBossEnemyAIController;
public:

	void SetSwitchLightActors(const TArray<ASwitchLightActor*>& NewSwitchLightActors) const { FirstStageSecondBossComponent->SetSwitchLightActors(NewSwitchLightActors);}
	void SetPointsLightsOnLevel(const TArray<APointLight*>& NewPointsLights) const { FirstStageSecondBossComponent->SetPointsLightsOnLevel(NewPointsLights);}

	void ChangeNiagaraVisibility(const bool&& NewBool) const{ SmokeNiagaraComponent->SetVisibility(NewBool);}

	void ChangeInvulnerable(const bool&& NewBool);

	void EndStage();
	void StartBoss();
};
