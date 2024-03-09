// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FirstStageSecondBossComponent.generated.h"


class APointLight;
class ASecondBossEnemy;
class UBehaviorTree;
class ASwitchLightActor;
class UNiagaraComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PSYCHO_API UFirstStageSecondBossComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFirstStageSecondBossComponent();
protected:
	virtual void BeginPlay() override;

	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="FirstStage")
	UBehaviorTree* FirstStageBehaviorTreeAsset;
	
	void ChangeIntensityAllLights(const float&);
	void EndFirstStage();
	UFUNCTION()
	void TurnOffSwitchLight(ASwitchLightActor* SwitchLightActor);
	void EnableSwitchLightActors();

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="FirstStage")
	float DimLight=30.0f;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="FirstStage")
	float BrightLight=100.0f;
	UPROPERTY()
	TArray<APointLight*> PointsLightsOnLevel;
	
	UPROPERTY()
	TArray<ASwitchLightActor*> SwitchLightsActors;
	UPROPERTY()
	TArray<ASwitchLightActor*> CurrentTurnedOnSwitchLightActors;
	UPROPERTY(EditAnywhere,Category="FirstStage",meta=(ClampMin=1))
	int32 HowManySwitchLightsActorsNeedEnable=1;

	UPROPERTY()
	ASecondBossEnemy* SecondBoss;
public:
	void FirstStageAction();

	void SetSwitchLightActors(const TArray<ASwitchLightActor*>& NewSwitchLightActors){SwitchLightsActors=NewSwitchLightActors;}
	void SetPointsLightsOnLevel(const TArray<APointLight*>& NewPointsLights){PointsLightsOnLevel=NewPointsLights;}

	UBehaviorTree* GetBehaviorTree() const {return FirstStageBehaviorTreeAsset;}
};
